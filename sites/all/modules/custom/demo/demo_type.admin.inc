<?php

/**
 * @file
 * Model type editing UI.
 */

/**
 * UI controller.
 */
class NotebookTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage notebook entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }
}

/**
 * Generates the notebook type editing form.
 */
function demo_type_form($form, &$form_state, $notebook, $op = 'edit') {

  if ($op == 'clone') {
    $notebook_type->label .= ' (cloned)';
    $notebook_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $notebook_type->label,
    '#description' => t('The human-readable name of this notebook type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($notebook_type->type) ? $notebook_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'demo_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this notebook type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['data']['#tree'] = TRUE;
  $form['data']['sample_data'] = array(
    '#type' => 'checkbox',
    '#title' => t('An interesting notebook switch'),
    '#default_value' => !empty($notebook_type->data['sample_data']),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save notebook type'),
    '#weight' => 40,
  );
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function demo_type_form_submit(&$form, &$form_state) {
  $notebook_type = entity_ui_form_submit_build_entity($form, $form_state);
  $notebook_type->save();
  $form_state['redirect'] = 'admin/structure/notebook_types';
}

/**
 * Form API submit callback for the delete button.
 */
function demo_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/notebook_types/manage/' . $form_state['notebook_type']->type . '/delete';
}
