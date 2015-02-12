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


  return $data;
}