<?php

/**
 * @file
 * Implements hook_theme().
 */


/**
 * IMPORTANT WARNING: DO NOT MODIFY THIS FILE.
 *
 */

 /*
 * Returns HTML for a fieldset form element and its children.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #attributes, #children, #collapsed, #collapsible,
 *     #description, #id, #title, #value.
 *
 * @ingroup themeable
 */
function groundwork_fieldset($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));
  $fieldset_wrapper_class = '';

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  if (!empty($element['#title'])) {
    // Always wrap fieldset legends in a SPAN for CSS positioning.
    $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';

    // add a class if a legend is being included
    $fieldset_wrapper_class = ' with-legend';
  }
  $output .= '<div class="fieldset-wrapper' . $fieldset_wrapper_class . '">';
  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= '</div>';
  $output .= "</fieldset>\n";
  return $output;
}

/**
 * Duplicate of theme_menu_local_tasks() but adds clearfix to tabs.
 */
function groundwork_menu_local_tasks(&$variables) {
  $output = '';

  if ($primary = drupal_render($variables['primary'])) {
    $output .= '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $output .= '<ul class="tabs primary clearfix">' . $primary . '</ul>';
  }
  if ($secondary = drupal_render($variables['secondary'])) {
    $output .= '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $output .= '<ul class="tabs secondary clearfix">' . $secondary . '</ul>';
  }

  return $output;
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function groundwork_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  // Determine if we are to display the breadcrumb.
  $show_breadcrumb = theme_get_setting('noceda_breadcrumb');
  if ($show_breadcrumb == 'yes' || $show_breadcrumb == 'admin' && arg(0) == 'admin') {

    // Optionally get rid of the homepage link.
    $show_breadcrumb_home = theme_get_setting('noceda_breadcrumb_home');
    if (!$show_breadcrumb_home) {
      array_shift($breadcrumb);
    }

    // Return the breadcrumb with separators.
    if (!empty($breadcrumb)) {
      $breadcrumb_separator = theme_get_setting('noceda_breadcrumb_separator');
      $trailing_separator = $title = '';
      if (theme_get_setting('noceda_breadcrumb_title')) {
        $item = menu_get_item();
        if (!empty($item['tab_parent'])) {
          // If we are on a non-default tab, use the tab's title.
          $title = check_plain($item['title']);
        }
        else {
          $title = drupal_get_title();
        }
        if ($title) {
          $trailing_separator = $breadcrumb_separator;
        }
      }
      elseif (theme_get_setting('noceda_breadcrumb_trailing')) {
        $trailing_separator = $breadcrumb_separator;
      }

      // Provide a navigational heading to give context for breadcrumb links.
      if (empty($variables['title'])) {
        $variables['title'] = t('You are here:');
      }
      if (theme_get_setting('noceda_breadcrumb_header')) {
        $variables['title_attributes_array']['class'][] = 'breadcrumb-header';
      }
      else {
        $variables['title_attributes_array']['class'][] = 'element-invisible';
      }
      $heading = '<span' . drupal_attributes($variables['title_attributes_array']) . '>' . $variables['title'] . '</span>';

      return '<nav id="breadcrumb" role="navigation" class="breadcrumb">' . $heading . implode($breadcrumb_separator, $breadcrumb) . $trailing_separator . '<span class="crumb-page">' . $title . '</span></nav>';
    }
  }
  // Otherwise, return an empty string.
  return '';
}
