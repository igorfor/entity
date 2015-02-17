<?php

/**
 * @file
 * Custom views handler definition.
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
      $image = array(
        'style_name' => 'thumbnail',
        'path' => $uri->photo, //
      );
    }

    return theme('image_style', $image);
  }
}