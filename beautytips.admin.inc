<?php
// $Id$

/**
 * @file
 * Beautytips settings form and submit action
 */

/**
 * Menu callback - beautytips admin settings form
 * TODO: Beautify this form so it's more usable and better looking
 */
function beautytips_admin() {
  drupal_add_css(drupal_get_path('module', 'beautytips') .'/css/beautytips.css');
  $form['beautytips_always_add'] = array(
    '#title' => t('Add beautytips js to every page'),
    '#description' => t('This allows you to give the class \'beautytips\' to any element on a page and the title attribute will popup as a beautytip.<br /> i.e. <i> &lt;p class="beautytips" title="type the text you want beautytips to display here"&gt .....&lt/p&gt</i>'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('beautytips_always_add', 0),
    '#weight' => -1,
  );
  $selectors = variable_get('beautytips_added_selectors_array', '');
  $form['beautytips_added_selectors_string'] = array(
    '#title' => t('Add beautytips to the following selectors'),
    '#description' => t("Separate selectors with a comma.  Beautytips will be added to each of these on every page.  The element's title attribute will be the text used. (OPTIONAL)"),
    '#type' => 'textfield',
    '#default_value' => is_array($selectors) ? implode(", ", $selectors) : '',
    '#weight' => -1,
  );
  $form['beautytips_default_styles'] = array(
    '#type' => 'fieldset',
    '#title' => 'Styling Options',
    '#collapsible' => TRUE,
    '#collapsible' => FALSE,
  );
  $form['beautytips_default_styles']['beautytips_default_style'] = array(
    '#type' => 'radios',
    '#title' => t('Choose a default style'),
    '#description' => t('Mouse over the radio buttons to see a preview.'),
    '#prefix' => '<div id="beauty-default-styles">',
    '#suffix' => '</div>',
    '#options' => array(
      'default' => t('default'),
      'netflix' => t('Netflix'),
      'facebook' => t('Facebook'),
      'transparent' => t('Transparent with Big Text'),
      'big_green' => t('Green with no border'),
      'google_maps' => t('Google Maps'),
    ),
    '#default_value' => variable_get('beautytips_default_style', 'default'),
  );  
  $style_options = array(
    'fill' => t('background color (string - html color)'), 
    'strokeWidth' => t('width of border (integer)'),
    'strokeStyle' => t('color of border (string - html color)'),
    'width' => t('width of popup (number in px)'), 
    'padding' => t('space between content and border (number in px)'), 
    'cornerRadius' => t('Controls roundness of corners (integer)'),
    'spikeGirth' => t('thickness of spike (integer)'),
    'spikeLength' => t('length of spike (integer)'),
    'shadowBlur' => t('Size of popup shadow (integer)'),
    'shadowColor' => t('Color of popup shadow (string - html color)'),
  ); 
  $form['beautytips_default_styles']['custom_styles'] = array(
    '#type' => 'fieldset',
    '#title' => 'Custom Style Options',
    '#description' => t('<b>Set a custom style.</b><br /> Note: These will use the default style that is selected as a base <br /> but will overide elements such as background color, border color etc.   <br /><i>Leave these empty unless you know what you are doing.</i><div id="beautytips-popup-changes"><div id="beauty-click-text"><p>Double Click here to view popup with custom changes</p></div></div>'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#prefix' => '<div id="beautytips-site-wide-popup"><div id="beauty-text"><p>Hover here to see the current site-wide beautytips</p></div></div>',
  );
  $custom_style = variable_get('beautytips_custom_style', NULL);
  foreach ($style_options as $option => $description) {
    $form['beautytips_default_styles']['custom_styles']['bt-options-' . $option] = array(
      '#title' => $option,
      '#description' => $description,
      '#type' => 'textfield',
      '#default_value' => isset($custom_style[$option]) ? $custom_style[$option] : '',
    );
  }
  $form['beautytips_default_styles']['custom_styles']['bt-options-shadow'] = array(
    '#title' => 'shadow',
    '#description' => t('Whether or not the popup has a shadow'),
    '#type' => 'checkbox',
    '#default_value' => isset($custom_style['shadow']) ? $custom_style['shadow'] : '',
  );
  

  $form['#submit'][] = 'beautytips_admin_submit';
  
  $path = drupal_get_path('module', 'beautytips') .'/js/bt_admin_page.js';
  drupal_add_js($path);
  beautytips_add_beautytips();

  if (module_exists('beautytips_ui')) {
    beautytips_ui_admin_settings($form); 
  }

  return system_settings_form($form);
}

/**
 * Submit function for beautytips settings form
 */
function beautytips_admin_submit($form, $form_state) {
  $values = $form_state['values'];
  if (count($values)) {
    $custom_style = array();
    foreach ($values as $option => $value) {
      if (strpos($option, 'bt-options-') === 0) {
        $option = str_replace('bt-options-', '', $option);
        $custom_style[$option] = $value;
      }
    }
    variable_set('beautytips_custom_style', $custom_style);
    variable_set('beautytips_default_style', $values['beautytips_default_style']);

    // Store the defaults - they will be passed to javascript
    $style = beautytips_get_default_style($values['beautytips_default_style']);
    if (count($custom_style)) {
      foreach ($custom_style as $option => $value) {
        if (!empty($value)) {
          $style[$option] = is_numeric($value) ? (int) $value : $value;
        }
      }
    }
    variable_set('beautytips_defaults', $style);

    // Store array of selectors that bt will be added to on every page
    $selectors = explode(",", $values['beautytips_added_selectors_string']);
    $test = serialize($selectors);
    if (count($selectors)) {
      foreach ($selectors as $key => $selector) {
        $selectors[$key] = trim($selector);
      }
    } 
    variable_set('beautytips_added_selectors_array', $selectors);
  }
  if (module_exists('beautytips_ui')) {
    beautytips_ui_admin_submit($form, $form_state);
  }
}

/**
 *  See jQuery.bt.js for descriptions of defaults
 */
function beautytips_get_default_style($style) {
  $bt_defaults = array();
  // The default style isn't necessarily needed here.
  switch ($style) {
    case 'default':
      $bt_defaults = array(
        'cssStyles' => array(),
      );
      break;
      
    case 'netflix':
      $bt_defaults = array(
        'positions' => array(0 => 'right', 1 => 'left'),
        'fill' => '#FFF',
        'padding' => 5,
        'shadow' => TRUE,
        'shadowBlur' => 12,
        'strokeStyle' => '#B9090B',
        'spikeLength' => 50,
        'spikeGirth' => 60,
        'cornerRadius' => 10,
        'centerPointY' => .1,
        'overlap' => -8,
        'cssStyles' => array(
          'fontSize' => '12px',
          'fontFamily' => 'arial,helvetica,sans-serif',
        ),
      );
      break;

    case 'facebook':
      $bt_defaults = array(
        'fill' => '#F7F7F7',
        'padding' => 8,
        'strokeStyle' => '#B7B7B7',
        'cornerRadius' => 0,
        'cssStyles' => array(
          'fontFamily' => '"lucida grande",tahoma,verdana,arial,sans-serif', 
          'fontSize' => '11px',
        ),
      );
      break;
      
    case 'transparent':
      $bt_defaults = array(
        'fill' => 'rgba(0, 0, 0, .8)',
        'padding' => 20,
        'strokeStyle' => '#CC0',
        'strokeWidth' => 3,
        'spikeLength' => 40,
        'spikeGirth' => 40,
        'cornerRadius' => 40,
        'cssStyles' => array(
          'color' => '#FFF',
          'fontWeight' => 'bold',
        ),
      );
      break;
      
      case 'big_green':
        $bt_defaults = array(
          'fill' => '#00FF4E',
          'padding' => 20,
          'strokeWidth' => 0,
          'spikeLength' => 40,
          'spikeGirth' => 40,
          'cornerRadius' => 15,
          'cssStyles' => array(
            'fontFamily' => '"lucida grande",tahoma,verdana,arial,sans-serif', 
            'fontSize' => '14px',
          ),
        );
        break;
        
        case 'google_maps':
          $bt_defaults = array(
            'positions' => array(0 => 'top', 1 => 'bottom'),
            'fill' => '#FFF',
            'padding' => 15,
            'strokeStyle' => '#ABABAB',
            'strokeWidth' => 1,
            'spikeLength' => 65,
            'spikeGirth' => 40,
            'cornerRadius' => 25,
            'centerPointX' => .9,
            'cssStyles' => array(),
          );
          break;
  }   
  return $bt_defaults;
}

