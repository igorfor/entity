<?php

/**
 * @file
 * Custom views handler definition.
 *
 * Place this code in
 * /sites/all/[custom_module_name]/includes/views_handler_my_custom_field.inc
 */

/**
 * Custom handler class.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_render_image extends views_handler_field {

  /**
   * @return array
   */

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  /**
   * @param $form
   * @param $form_state
   */

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  /**
   * @param $values
   * @return string
   * Render callback handler.
   * Return the markup that will appear in the rendered field.
   */

  function render($values) {
    $uris = db_select('address_book', 'ab')
      ->fields('ab', array('photo'))
      ->execute();
    foreach ($uris as $uri) {
      $images = file_create_url($uri->photo);
      $arbitrary_array = array(
        'path' => $images,
        'alt' => 'Alternate Text',
        'title' => 'Image Title',
        'width' => '100px',
        'height' => '100px',
        'attributes' => array('class' => 'some-img', 'id' => 'my-img'),
      );
    }
    return theme_image($arbitrary_array);
  }
}