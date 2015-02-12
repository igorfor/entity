<?php

/**
 * @file
 * Notebook editing UI.
 */

/**
 * UI controller.
 */
class NotebookUIController extends EntityDefaultUIController {

  public function hook_menu() {

    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Notebooks',
      'description' => 'Add edit and update notebooks.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );

    // Change the overview menu type for the list of notebooks.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a notebook',
      'description' => 'Add a new notebook',
      'page callback'  => 'demo_add_page',
      'access callback'  => 'demo_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'demo.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );

    // Add menu items to add each different type of entity.
    foreach (demo_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'demo_form_wrapper',
        'page arguments' => array(demo_create(array('type' => $type->type))),
        'access callback' => 'demo_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'demo.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing notebook entities
    $items[$this->path . '/notebook/' . $wildcard] = array(
      'page callback' => 'demo_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'demo_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'demo.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/notebook/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$this->path . '/notebook/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'demo_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'notebook_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'demo.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    // Menu item for viewing notebooks
    $items['notebook/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'demo_page_title',
      'title arguments' => array(1),
      'page callback' => 'demo_page_view',
      'page arguments' => array(1),
      'access callback' => 'demo_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }


  /**
   * Create the markup for the add Notebook Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }

    return theme('demo_add_list', array('content' => $content));
  }

}


/**
 * Form callback wrapper: create or edit a notebook.
 *
 * @param $notebook
 *   The notebook object being edited by this form.
 *
 * @see notebook_edit_form()
 */
function notebook_form_wrapper($notebook) {

  notebook_set_breadcrumb();
  return drupal_get_form('demo_edit_form', $notebook);
}


/**
 * Form callback wrapper: delete a notebook.
 *
 * @param $notebook
 *   The notebook object being edited by this form.
 *
 * @see notebook_edit_form()
 */
function demo_delete_form_wrapper($notebook) {
  // Add the breadcrumb for the form's location.
  //notebook_set_breadcrumb();
  return drupal_get_form('demo_delete_form', $notebook);
}


/**
 * Form callback: create or edit a notebook.
 *
 * @param $notebook
 *   The notebook object to edit or for a create form an empty notebook object
 *     with only a notebook type defined.
 */
function demo_edit_form($form, &$form_state, $notebook) {
  // Add the default field elements.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Notebook Name'),
    '#default_value' => isset($notebook->name) ? $notebook->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  $form['data']['#tree'] = TRUE;
  $form['data']['sample_data'] = array(
    '#type' => 'checkbox',
    '#title' => t('An interesting notebook switch'),
    '#default_value' => isset($notebook->data['sample_data']) ? $notebook->data['sample_data'] : 1,
  );

  // Add the field related form elements.
  $form_state['notebook'] = $notebook;
  field_attach_form('notebook', $notebook, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save notebook'),
    '#submit' => $submit + array('notebook_edit_form_submit'),
  );

  if (!empty($notebook->name)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete notebook'),
      '#suffix' => l(t('Cancel'), 'admin/content/notebooks'),
      '#submit' => $submit + array('notebook_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'demo_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the notebook form
 */
function demo_edit_form_validate(&$form, &$form_state) {
  $notebook = $form_state['notebook'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('notebook', $notebook, $form, $form_state);
}


/**
 * Form API submit callback for the notebook form.
 *
 *
 */
function demo_edit_form_submit(&$form, &$form_state) {

  $notebook = entity_ui_controller('notebook')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the notebook and go back to the list of notebooks

  // Add in created and changed times.
  if ($notebook->is_new = isset($notebook->is_new) ? $notebook->is_new : 0){
    $notebook->created = time();
  }

  $notebook->changed = time();

  $notebook->save();
  $form_state['redirect'] = 'admin/content/notebooks';
}

/**
 * Form API submit callback for the delete button.
 *
 *
 */
function demo_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/notebooks/notebook/' . $form_state['notebook']->notebook_id . '/delete';
}


/**
 * Form callback: confirmation form for deleting a notebook.
 *
 * @param $notebook
 *   The notebook to delete
 *
 * @see confirm_form()
 */
function demo_delete_form($form, &$form_state, $notebook) {
  $form_state['notebook'] = $notebook;

  $form['#submit'][] = 'demo_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete notebook %name?', array('%name' => $notebook->name)),
    'admin/content/notebooks/notebook',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for notebook_delete_form
 */
function demo_delete_form_submit($form, &$form_state) {
  $notebook = $form_state['notebook'];

  demo_delete($notebook);

  drupal_set_message(t('The notebook %name has been deleted.', array('%name' => $notebook->name)));
  watchdog('notebook', 'Deleted notebook %name.', array('%name' => $notebook->name));

  $form_state['redirect'] = 'admin/content/notebooks';
}



/**
 * Page to add Notebook Entities.
 *
 *
 */
function demo_add_page() {
  $controller = entity_ui_controller('notebook');
  return $controller->addPage();
}


/**
 * Displays the list of available notebook types for notebook creation.
 *
 * @ingroup themeable
 */
function theme_demo_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="notebook-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer notebook types')) {
      $output = '<p>' . t('Notebook Entities cannot be added because you have not created any notebook types yet. Go to the <a href="@create-notebook-type">notebook type creation page</a> to add a new notebook type.', array('@create-notebook-type' => url('admin/structure/notebook_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No notebook types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}





/**
 * Sets the breadcrumb for administrative notebook pages.
 */
function demo_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Notebooks'), 'admin/content/notebooks'),
  );

  drupal_set_breadcrumb($breadcrumb);
}



