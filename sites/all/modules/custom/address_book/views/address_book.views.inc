<?php

/**
 * Implements hook_views_data().
 */
function address_book_views_data() {
  $data = array();
  $data['address_book']['table']['group'] = t('Address Book');
  $data['address_book']['table']['base'] = array (
    'field' => 'basic_id',
    'title' => t('Address Book'),
  );
  $data['address_book']['table']['entity type'] = 'address_book';

  $data['address_book']['basic_id'] = array (
    'title' => t('Address Book ID'),
    'help' => t('The unique internal identifier of the Address book.'),
    'field' => array  (
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'argument' => array(
      'handler' => 'views_handler_field',
      'name field' => 'basic_id',
      'numeric' => TRUE,
      'validate type' => 'id',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['address_book']['name'] = array(
    'title' => t('User name'),
    'help' => t('User name'),
    'field' => array(
      'field' => 'name',
      'group' => t('Address Book'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
      'argument' => array(
      'handler' => 'views_handler_field',
    ),

    'filter' => array(
      'handler' => 'views_handler_field_filter_format_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['address_book']['last_name'] = array (
    'title' => t('User last name'),
    'help' => t('User last name'),
    'field' => array(
      'field' => 'last_name',
      'group' => t('Address Book'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_field',
    ),

    'filter' => array(
      'handler' => 'views_handler_field_filter_format_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['address_book']['phone'] = array(
    'title' => t('User phone'),
    'help' => t('User phone'),
    'field' => array(
      'field' => 'phone',
      'group' => t('Address Book'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_field',
    ),

    'filter' => array(
      'handler' => 'views_handler_field_filter_format_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['address_book']['created'] = array(
    'title' => t('Post date'),
    'help' => t('The date the address book  was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  $data['address_book']['photo'] = array (
    'title' => t('User photo'),
    'help' => t('User photo'),
    'field' => array(
      'field' => 'photo',
      'group' => t('Address Book'),
      'handler' => 'views_handler_field_render_image',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_field',
    ),


  );


  return $data;
}

/**
 * Implements hook_views_default_views().
 */
function address_book_views_default_views() {
  $view = new view();
  $view->name = 'address_book_entity';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'address_book';
  $view->human_name = 'address book entity';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'address book entity';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'basic_id' => 'basic_id',
    'created' => 'created',
    'name' => 'name',
    'field_image' => 'field_image',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'basic_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_image' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Address Book: User name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'address_book';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Address Book: User last name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'address_book';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Address Book: User phone */
  $handler->display->display_options['fields']['phone']['id'] = 'phone';
  $handler->display->display_options['fields']['phone']['table'] = 'address_book';
  $handler->display->display_options['fields']['phone']['field'] = 'phone';
  /* Field: Address Book: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'address_book';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Address Book: Address Book ID */
  $handler->display->display_options['fields']['basic_id']['id'] = 'basic_id';
  $handler->display->display_options['fields']['basic_id']['table'] = 'address_book';
  $handler->display->display_options['fields']['basic_id']['field'] = 'basic_id';
  /* Field: Address Book: User photo */
  $handler->display->display_options['fields']['photo']['id'] = 'photo';
  $handler->display->display_options['fields']['photo']['table'] = 'address_book';
  $handler->display->display_options['fields']['photo']['field'] = 'photo';
  $handler->display->display_options['fields']['photo']['element_label_colon'] = FALSE;
  /* Field: Bulk operations: Address Book */
  $handler->display->display_options['fields']['views_bulk_operations_1']['id'] = 'views_bulk_operations_1';
  $handler->display->display_options['fields']['views_bulk_operations_1']['table'] = 'address_book';
  $handler->display->display_options['fields']['views_bulk_operations_1']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_operations'] = array(
    'action::address_book_remove_entity' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'address-book/list';

  $views[$view->name] = $view;
  return $views;
}
