<?php

/**
 * @file
 * Preprocess and process variables.
 */


/**
 * Preprocess variables for html.tpl.php
 */
function groundwork_preprocess_html(&$variables) {
  // Uses RDFa attributes if the RDF module is enabled. Lifted from adaptivethemes.
  if (module_exists('rdf')) {
    $variables['doctype'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML+RDFa 1.1//EN">' . "\n";
    $variables['rdf']->version = 'version="HTML+RDFa 1.1"';
    $variables['rdf']->namespaces = $variables['rdf_namespaces'];
    $variables['rdf']->profile = ' profile="' . $variables['grddl_profile'] . '"';
  }
  else {
    $variables['doctype'] = '<!DOCTYPE html>' . "\n";
    $variables['rdf']->version = '';
    $variables['rdf']->namespaces = '';
    $variables['rdf']->profile = '';
  }
  // Optionally adds the CSS class to display a background guide
  if (theme_get_setting('noceda_background_guide')) {
    $variables['classes_array'][] = 'with-bg-guide';
  }
  // Optionally adds the CSS class to display wthe grid
  if (theme_get_setting('noceda_grid')) {
    $variables['classes_array'][] = 'with-grid';
  }
  // Optionally adds the CSS class to display form field icons.
  if (theme_get_setting('noceda_form_field_icons')) {
    $variables['classes_array'][] = 'noceda-form-field-icons';
  }
  // Optionally adds the CSS class to remove form labels.
  if (theme_get_setting('noceda_form_field_icons_label')) {
    $variables['classes_array'][] = 'no-form-labels';
  }
  // Optionally adds the CSS class to display block icons.
  if (theme_get_setting('noceda_block-icons')) {
    $variables['classes_array'][] = 'noceda-block-icons';
  }
  // Optionally adds additional stylesheets and js files.
  if (theme_get_setting('noceda_formalize')) {
    drupal_add_css(drupal_get_path('theme', 'groundwork') . '/css/formalize.css', array('group' => CSS_THEME, 'preprocess' => TRUE));
    drupal_add_js(drupal_get_path('theme', 'groundwork') . '/js/jquery.formalize.min.js', array('group' => JS_THEME, 'every_page' => TRUE, 'preprocess' => TRUE));
  }
  $path = drupal_get_path('theme', variable_get('theme_default', NULL));
  if (file_exists($path . '/css/local.css')) {
    drupal_add_css($path . '/css/local.css', array('group' => CSS_THEME, 'preprocess' => TRUE));
  }
}

/**
 * Preprocess variables for page.tpl.php
 */
function groundwork_preprocess_page(&$variables) {
  // Set correct title to user pages.
  if (arg(0) == 'user' && arg(1) == 'login') {
    drupal_set_title(t('User login'));
  }
  if (arg(0) == 'user' && arg(1) == 'password') {
    drupal_set_title(t('Request new password'));
  }
  if (arg(0) == 'user' && arg(1) == 'register') {
    drupal_set_title(t('Create new account'));
  }
  if (theme_get_setting('noceda_hide_attribution')) {
    $variables['attribution'] = '';
  }
  else {
    $variables['attribution'] = '<div id="theme-attribution"><div class="grid-12 alpha">Powered by <a href="http://drupal.org">Drupal</a> Content Management System</div><div class="grid-12 omega">Groundwork Theme Framework by <a href="http://www.noceda.no" title="Spesialister på Drupal i Norge">Noceda Media Lab</a></div></div>';
  }
}

/**
 * Process variables for page.tpl.php
 */
function groundwork_process_page(&$variables) {
   // Since the title and the shortcut link are both block level elements,
  // positioning them next to each other is much simpler with a wrapper div.
  if (!empty($variables['title_suffix']['add_or_remove_shortcut']) && $variables['title']) {
    // Add a wrapper div using the title_prefix and title_suffix render elements.
    $variables['title_prefix']['shortcut_wrapper'] = array(
      '#markup' => '<div class="shortcut-wrapper clearfix">',
      '#weight' => 100,
    );
    $variables['title_suffix']['shortcut_wrapper'] = array(
      '#markup' => '</div>',
      '#weight' => -99,
    );
    // Make sure the shortcut link is the first item in title_suffix.
    $variables['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
  }
}

/**
 * Preprocess variables for region.tpl.php
 * Override or insert variables into the region template.
 *
 */
function groundwork_preprocess_region(&$variables, $hook) {
  $variables['classes_array'][] = 'clearfix';
}

/**
 * Preprocess variables for node.tpl.php
 * Override or insert variables into the node template.
 *
 */
function groundwork_preprocess_node(&$variables) {
  $variables['submitted'] = t('Published by !username on !datetime', array('!username' => $variables['name'], '!datetime' => $variables['date']));
  $variables['classes_array'][] = $variables['zebra'];
  $variables['classes_array'][] = 'node-count-' . $variables['id'];
  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
  }
  // Optionally adds the CSS class to hide the book navigation.
  if ($variables['type'] == 'book') {
    if (theme_get_setting('noceda_book_navigation')) {
    $variables['classes_array'][] = 'no-book-navigation';
    }
  }
  $variables['attributes_array']['role'][] = 'article';
  $variables['title_attributes_array']['class'][] = 'node-title';
  $variables['content_attributes_array']['class'][] = 'node-content';
  // add a $node_aside variable.
  if ($blocks = block_get_blocks_by_region('aside')) {
    $variables['node_aside'] = $blocks;
    $variables['node_aside'] = $blocks;
    $variables['node_aside']['#theme_wrappers'] = array('region');
    $variables['node_aside']['#region'] = 'aside';
    // add a class to the node as well, for easy styling.
    $variables['classes_array'][] = 'with-aside';
  }
  else {
    $variables['node_aside'] = '';
  }
}

/**
 * Preprocess variables for block.tpl.php
 * Override or insert variables into the block template.
 *
 */
function groundwork_preprocess_block(&$variables, $hook) {
  $variables['classes_array'][] = 'block-' . $variables['block_zebra'];
  $variables['classes_array'][] = drupal_html_class('block-region-' . $variables['block']->region);
  // add odd/even CSS classes into the array of classes
  if ($variables['block_id'] == 1) {
    $variables['classes_array'][] = 'block-first';
  }
  // theme setting. option for inline login block
  if ($variables['block']->module == 'user' && $variables['block']->delta == 0) {
    if (theme_get_setting('noceda_horizontal_login_block')) {
      $variables['classes_array'][] = 'horizontal-login-block';
    }
  }
  // The last_in_region property is set in noceda_page_alter().
  if (isset($variables['block']->last_in_region)) {
    $variables['classes_array'][] = 'block-last';
  }
  if ($variables['block_id'] == 1 && isset($variables['block']->last_in_region)) {
    $variables['classes_array'][] = 'block-alone';
  }
  $variables['title_attributes_array']['class'][] = 'block-title';
  if ($variables['block']->region == 'navigation' || $variables['block']->region == 'topbar') {
    $variables['title_attributes_array']['class'][] = 'element-invisible';
  }
  $variables['content_attributes_array']['class'][] = 'block-content';
  if (empty($variables['block']->subject)) {
    $variables['content_attributes_array']['class'][] = 'block-no-title';
  }
  $variables['content_attributes_array']['class'][] = 'content';
  // Provide template suggestions
  $variables['theme_hook_suggestions'][] = 'block__' . $variables['block']->region . '__' . $variables['block']->module;
  $nav_blocks = array('navigation', 'main-menu', 'user-menu', 'management');
  if (in_array($variables['block']->delta, $nav_blocks)) {
    $variables['theme_hook_suggestions'][] = 'block__menu';
  }
  $nav_modules = array('superfish', 'nice_menus');
  if (in_array($variables['block']->module, $nav_modules)) {
    $variables['theme_hook_suggestions'][] = 'block__menu';
  }
  // Add ARIA Roles to blocks, lifted from adaptivethemes.
  $roles = array(
    'complementary' => array(
      'aggregator',
      'help',
      'locale',
      'poll',
      'profile',
      'node' => array('syndicate'),
      'system' => array('powered-by', 'help'),
      'user' => array('new', 'online'),
    ),
    'navigation' => array(
      'blog',
      'book',
      'comment',
      'forum',
      'menu',
      'menu_block',
      'node' => array('recent'),
      'shortcut',
      'statistics',
      'system' => array_keys(menu_list_system_menus()),
      'superfish',
      'nice_menus',
    ),
    'search' => array(
      'search',
    ),
    'form' => array(
      'user' => array('login'),
    ),
  );
  foreach ($roles as $role => $module) {
    if (!is_array($role) && in_array($variables['block']->module, $module)) {
      $variables['attributes_array']['role'] = "$role";
    }
    elseif (is_array($role)) {
      foreach ($role as $module => $delta) {
        if ($variables['block']->module == $module && in_array($variables['block']->delta, $delta)) {
          $variables['attributes_array']['role'] = "$role";
        }
      }
    }
  }
}

/**
 * Preprocess variables for comment.tpl.php
 */
function groundwork_preprocess_comment(&$variables) {
  $variables['title_attributes_array']['class'][] = 'comment-title';
  $variables['content_attributes_array']['class'][] = 'comment-content';
}

/**
 * Preprocess variables for maintenance-page.tpl.php
 */
function groundwork_preprocess_maintenance_page(&$variables) {
  $variables['attribution'] = '<div id="theme-attribution"><div class="grid-12 alpha">Powered by <a href="http://drupal.org">Drupal</a> Content Management System</div><div class="grid-12 omega">Groundwork Theme Framework by <a href="http://www.noceda.no" title="Spesialister på Drupal i Norge">Noceda Media Lab</a></div></div>';
}

/**
 * Override or insert variables into theme_menu_local_task().
 */
function groundwork_preprocess_menu_local_task(&$variables) {
  $link =& $variables['element']['#link'];

  // If the link does not contain HTML already, check_plain() it now.
  // After we set 'html'=TRUE the link will not be sanitized by l().
  if (empty($link['localized_options']['html'])) {
    $link['title'] = check_plain($link['title']);
  }
  $link['localized_options']['html'] = TRUE;
  $link['title'] = '<span class="tab">' . $link['title'] . '</span>';
}

/**
 * Changes the search form to use the HTML5 "search" input attribute.
 */
function groundwork_preprocess_search_block_form(&$variables) {
  $variables['search_form'] = str_replace('type="text"', 'type="search"', $variables['search_form']);
  $variables['search_form'] = str_replace('size="15"', 'size="20"', $variables['search_form']);
}

function groundwork_preprocess_search_result(&$variables) {
  global $language;

  $result = $variables['result'];
  $variables['url'] = check_url($result['link']);
  $variables['title'] = check_plain($result['title']);
  if (isset($result['language']) && $result['language'] != $language->language && $result['language'] != LANGUAGE_NONE) {
    $variables['title_attributes_array']['xml:lang'] = $result['language'];
    $variables['content_attributes_array']['xml:lang'] = $result['language'];
  }

  $info = array();
  if (!empty($result['type']) && theme_get_setting('noceda_search_type')) {
    $info['module'] = check_plain($result['type']);
  }
  if (!empty($result['user']) && theme_get_setting('noceda_search_user')) {
    $info['user'] = $result['user'];
  }
  if (!empty($result['date']) && theme_get_setting('noceda_search_date')) {
    $info['date'] = format_date($result['date'], 'short');
  }
  if (isset($result['extra']) && is_array($result['extra'])) {
    if (!empty($result['extra'][0]) && theme_get_setting('noceda_search_comment')) {
      $info['comment'] = $result['extra'][0];
    }
    if (!empty($result['extra'][1]) && theme_get_setting('noceda_search_upload')) {
      $info['upload'] = $result['extra'][1];
    }
  }
  // Check for existence. User search does not include snippets.
  $variables['snippet'] = isset($result['snippet']) ? $result['snippet'] : '';
  // Provide separated and grouped meta information..
  $variables['info_split'] = $info;
  $variables['info'] = implode(' - ', $info);
  $variables['theme_hook_suggestions'][] = 'search_result__' . $variables['module'];
}
