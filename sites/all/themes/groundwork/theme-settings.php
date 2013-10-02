<?php

/**
 * @file
 * Implements hook_form_system_theme_settings_alter() function.
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */

function groundwork_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL) {

  // Double invoke bug in core: http://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }

  // Layout settings
  $form['groundwork'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => -10,
  );

  // General Settings
  $form['groundwork']['general_settings'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('General settings'),
  );

  // Helper Libraries
  $form['groundwork']['general_settings']['noceda_formalize'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Formalize'),
    '#description'   => t('Use the Formalize package on forms. The <a href="!link">Formalize CSS Framework</a> is for nice looking, HTML5 ready, progressively enhanced, cross-browser forms.', array('!link' => 'http://formalize.me')),
    '#default_value' => theme_get_setting('noceda_formalize'),
  );
  // Inline Login Block
  $form['groundwork']['general_settings']['noceda_horizontal_login_block'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Horizontal Login Block'),
    '#description'   => t('Display the user login block horizontally. Note that additional login options (eg. OpenID, Facebook, Twitter etc.  are not supported)'),
    '#default_value' => theme_get_setting('noceda_horizontal_login_block'),
  );
  // Hide Book Navigation
  $form['groundwork']['general_settings']['noceda_book_navigation'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Hide book navigation'),
    '#description'   => t('Useful if you will use a block to display the book navigation. Eg., on Aside region.'),
    '#default_value' => theme_get_setting('noceda_book_navigation'),
  );
  // Hide Theme Attribution
  $form['groundwork']['general_settings']['noceda_hide_attribution'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Hide theme attribution'),
    '#description'   => t('Useful if you have customized this theme.'),
    '#default_value' => theme_get_setting('noceda_hide_attribution'),
  );

  // Icon Settings
  $form['groundwork']['icon_settings'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Icon settings'),
  );
  // Form Field Icons
  $form['groundwork']['icon_settings']['noceda_form_field_icons'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Display form field icons'),
    '#description'   => t('Use icons for some common form fields (Username, password, and search).'),
    '#default_value' => theme_get_setting('noceda_form_field_icons'),
  );
  $form['groundwork']['icon_settings']['noceda_form_field_icons_label'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Hide the labels.'),
    '#description'   => t('Hide the labels on form fields with icons.'),
    '#default_value' => theme_get_setting('noceda_form_field_icons_label'),
  );
  // Block Icons
  $form['groundwork']['icon_settings']['noceda_block_icons'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Display block icons'),
    '#description'   => t('Use icons for some common blocks (Username, password, and search).'),
    '#default_value' => theme_get_setting('noceda_block_icons'),
  );

  // Search setting
  $form['groundwork']['search_settings'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Search settings'),
  );
  $form['groundwork']['search_settings']['noceda_search_type'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Node type'),
    '#description'   => t('Display the node type (or item type string supplied by module).'),
    '#default_value' => theme_get_setting('noceda_search_type'),
  );
  $form['groundwork']['search_settings']['noceda_search_user'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Author'),
    '#description'   => t('Display the author of the node linked to users profile. Depends on permission.'),
    '#default_value' => theme_get_setting('noceda_search_user'),
  );
  $form['groundwork']['search_settings']['noceda_search_date'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Date'),
    '#description'   => t('Display the last update date of the node. Short formatted.'),
    '#default_value' => theme_get_setting('noceda_search_date'),
  );
  $form['groundwork']['search_settings']['noceda_search_comment'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Comments'),
    '#description'   => t('Display the number of comments output as "% comments", % being the count.'),
    '#default_value' => theme_get_setting('noceda_search_comment'),
  );
  $form['groundwork']['search_settings']['noceda_search_upload'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Attachments'),
    '#description'   => t('Display the number of attachments.'),
    '#default_value' => theme_get_setting('noceda_search_upload'),
  );

  // Breadcrumb
  $form['groundwork']['breadcrumb'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Breadcrumb settings'),
  );
  $form['groundwork']['breadcrumb']['noceda_breadcrumb'] = array(
    '#type'          => 'select',
    '#title'         => t('Display breadcrumb'),
    '#default_value' => theme_get_setting('noceda_breadcrumb'),
    '#options'       => array(
                          'yes'   => t('Yes'),
                          'admin' => t('Only in admin section'),
                          'no'    => t('No'),
                        ),
  );
  $form['groundwork']['breadcrumb']['breadcrumb_options'] = array(
    '#type' => 'container',
    '#states' => array(
      'invisible' => array(
        ':input[name="noceda_breadcrumb"]' => array('value' => 'no'),
      ),
    ),
  );
  $form['groundwork']['breadcrumb']['breadcrumb_options']['noceda_breadcrumb_header'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Prepend a "You are here:" at the start of  breadcrumb'),
    '#default_value' => theme_get_setting('noceda_breadcrumb_header'),
  );
  $form['groundwork']['breadcrumb']['breadcrumb_options']['noceda_breadcrumb_home'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Show home page link in breadcrumb'),
    '#default_value' => theme_get_setting('noceda_breadcrumb_home'),
  );
  $form['groundwork']['breadcrumb']['breadcrumb_options']['noceda_breadcrumb_separator'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Breadcrumb separator'),
    '#description'   => t('Text only. Don’t forget to include spaces.'),
    '#default_value' => theme_get_setting('noceda_breadcrumb_separator'),
    '#size'          => 5,
    '#maxlength'     => 10,
  );
  $form['groundwork']['breadcrumb']['breadcrumb_options']['noceda_breadcrumb_trailing'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Append a separator to the end of the breadcrumb'),
    '#default_value' => theme_get_setting('noceda_breadcrumb_trailing'),
    '#description'   => t('Useful when the breadcrumb is placed just before the title.'),
    '#states' => array(
      'disabled' => array(
        ':input[name="noceda_breadcrumb_title"]' => array('checked' => TRUE),
      ),
      'unchecked' => array(
        ':input[name="noceda_breadcrumb_title"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['groundwork']['breadcrumb']['breadcrumb_options']['noceda_breadcrumb_title'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Append the content title to the end of the breadcrumb'),
    '#default_value' => theme_get_setting('noceda_breadcrumb_title'),
    '#description'   => t('Useful when the breadcrumb is not placed just before the title.'),
  );
  // Theme Development
  $form['groundwork']['themedev'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Theme development settings'),
  );
  $form['groundwork']['themedev']['noceda_grid'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Show grids around main layout elements'),
    '#default_value' => theme_get_setting('noceda_grid'),
  );
  $form['groundwork']['themedev']['noceda_background_guide'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Add background guides in blocks'),
    '#default_value' => theme_get_setting('noceda_background_guide'),
    '#description'   => t('Shows a baby pink background in blocks as easy guides for your block layouts.'),
  );

  $form['theme_settings']['#collapsible'] = TRUE;
  $form['theme_settings']['#collapsed'] = TRUE;
  $form['logo']['#collapsible'] = TRUE;
  $form['logo']['#collapsed'] = TRUE;
  $form['favicon']['#collapsible'] = TRUE;
  $form['favicon']['#collapsed'] = TRUE;
}