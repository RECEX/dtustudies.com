<?php

/**
 * @file
 * Performs different alterations.
 */

 /**
 * Changes the default meta content-type tag to the shorter HTML5 version
 */
function groundwork_html_head_alter(&$head_elements) {
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8'
  );
}

/**
 * Sets a class on the iframe body element for WYSIWYG editors. This allows
 * to easily override the background for the iframe body element.
 * This only works for the WYSIWYG module: http://drupal.org/project/wysiwyg
 */
function groundwork_wysiwyg_editor_settings_alter(&$settings, &$context) {
  $settings['bodyClass'] = 'wysiwyg-editor';
}

/**
 * Implements hook_page_alter().
 */
function groundwork_page_alter($page) {
  // Look in each visible region for blocks.
  foreach (system_region_list($GLOBALS['theme'], REGIONS_VISIBLE) as $region => $name) {
    if (!empty($page[$region])) {
      // Find the last block in the region.
      $blocks = array_reverse(element_children($page[$region]));
      while ($blocks && !isset($page[$region][$blocks[0]]['#block'])) {
        array_shift($blocks);
      }
      if ($blocks) {
        $page[$region][$blocks[0]]['#block']->last_in_region = TRUE;
      }
    }
  }
}