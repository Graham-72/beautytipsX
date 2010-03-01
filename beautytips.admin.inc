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
      'hulu' => t('Hulu'),
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
    '#title' => t('Custom Style Options'),
    '#description' => t('<b>Set a custom style.</b><br /> Note: These will use the default style that is selected as a base <br /> but will overide elements such as background color, border color etc.   <br /><i>Leave these empty unless you know what you are doing.</i><div id="beautytips-popup-changes"><div id="beauty-click-text"><p>Double Click here to view popup with custom changes</p></div></div>'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => 'bt-custom-styles'),
    '#prefix' => '<div id="beautytips-site-wide-popup"><div id="beauty-text"><p>Hover here to see the current site-wide beautytips</p></div></div>',
  );
  $custom_style = variable_get('beautytips_custom_style', NULL);
  foreach ($style_options as $option => $description) {
    $form['beautytips_default_styles']['custom_styles']['bt-options-box-' . $option] = array(
      '#title' => $option,
      '#description' => $description,
      '#type' => 'textfield',
      '#default_value' => isset($custom_style[$option]) ? $custom_style[$option] : '',
    );
  }
  // TODO: make this a radio (default, shadow, no-shadow)
  $form['beautytips_default_styles']['custom_styles']['bt-options-box-shadow'] = array(
    '#title' => 'shadow',
    '#description' => t('Whether or not the popup has a shadow'),
    '#type' => 'radios',
    '#options' => array('default' => t('Default'), 'shadow' => t('Shadow On'), 'no_shadow' => t('Shadow Off')),
    '#attributes' => array('class' => 'beautytips-options-shadow'),
    '#default_value' => isset($custom_style['shadow']) ? $custom_style['shadow'] : 'default',
  );
  $form['beautytips_default_styles']['custom_styles']['bt-options-cssClass'] = array(
    '#title' => 'cssClass',
    '#description' => t('The class that will be applied to the box wrapper div (of the TIP)'),
    '#type' => 'textfield',
    '#default_value' => isset($custom_style['cssClass']) ? $custom_style['cssClass'] : '',
  );
  $css_style_options = array('color', 'fontFamily', 'fontWeight', 'fontSize');
  $form['beautytips_default_styles']['custom_styles']['css-styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Font Styling'),
    '#description' => t('Enter css options for changing the font style'),
    '#attributes' => array('class' => 'beautytips-css-styling'),
    '#collapsible' => FALSE,
  );
  foreach ($css_style_options as $option) {
    $form['beautytips_default_styles']['custom_styles']['css-styles']['bt-options-css-' . $option] = array(
      '#title' => $option,
      '#type' => 'textfield',
      '#default_value' => isset($custom_style['cssStyles'][$option]) ? $custom_style['cssStyles'][$option] : '',
    );
  }

  $form['#submit'][] = 'beautytips_admin_submit';
  
  $path = drupal_get_path('module', 'beautytips');
  drupal_add_js($path . '/other_libs/colorpicker/js/colorpicker.js');
  drupal_add_css($path . '/other_libs/colorpicker/css/colorpicker.css');
  drupal_add_css($path .'/css/beautytips.css');
  drupal_add_css($path .'/css/beautytips_admin.css');
  beautytips_add_beautytips();
  drupal_add_js($path . '/js/bt_admin_page.js');

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
    $css_style = array();
    foreach ($values as $option => $value) {
      if (strpos($option, 'bt-options-box-') === 0) {
        $option = str_replace('bt-options-box-', '', $option);
        $custom_style[$option] = $value;
      }
      if (strpos($option, 'bt-options-css-') === 0) {
        $option = str_replace('bt-options-css-', '', $option);
        if ($value) {
          $css_style[$option] = $value;
        }
      }
    }

    // Store the defaults - they will be passed to javascript
    $style = beautytips_get_default_style($values['beautytips_default_style']);
    if (count($custom_style)) {
      foreach ($custom_style as $option => $value) {
        if ($option == 'shadow') {
          if ($value != 'default') {
            $style['shadow'] = $value == 'shadow' ? TRUE : FALSE;
          }
        }
        else if (!empty($value) || $value == '0') {
          $style[$option] = is_numeric($value) ? (int) $value : (string) $value;
        }
      }
    }
    if (count($css_style)) {
      foreach ($css_style as $option => $value) {
        if (!empty($value)) {
          $style['cssStyles'][$option] = (string) $value;
        }
      }
      if (!empty($css_style)) {
        $custom_style['cssStyles'] = $css_style;
      }
    }
    variable_set('beautytips_defaults', $style);
    variable_set('beautytips_custom_style', $custom_style);
    variable_set('beautytips_default_style', $values['beautytips_default_style']);

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

        case 'hulu':
          $bt_defaults = array(
            'fill' => '#F4F4F4',
            'strokeStyle' => '#666666', 
            'spikeLength' => 20,
            'spikeGirth' => 10,
            'width' => 350,
            'overlap' => 0,
            'centerPointY' => 1,
            'cornerRadius' => 0, 
            'cssStyles' => array(
              'fontFamily' => '"Lucida Grande",Helvetica,Arial,Verdana,sans-serif', 
              'fontSize' => '12px',
              'padding' => '10px 14px'
            ),
            'shadow' => TRUE,
            'shadowColor' => 'rgba(0,0,0,.5)',
            'shadowBlur' => 8,
            'shadowOffsetX' => 4,
            'shadowOffsetY' => 4,
          );
          break;
  }   
  return $bt_defaults;
}

