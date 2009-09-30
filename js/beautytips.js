Drupal.behaviors.beautytips = function() {
  jQuery.bt.defaults.closeWhenOthersOpen = true;
  beautytips_defaults = Drupal.settings.beautytips_defaults;
  beautytips = Drupal.settings.beautytips;

  // Set default css settings as chosen in BeautyTips settings
  if ( beautytips_defaults['css_list'].length > 0) {
    for (var j = 0; j < beautytips_defaults['css_list'].length; j++) {
      jQuery.bt.defaults.cssStyles[beautytips_defaults['css_list'][0]] = beautytips_defaults['cssStyles'][beautytips_defaults['css_list'][0]];
    }
  }
  // Defaults based on which style was chosen in BeautyTips Settings
  if (beautytips_defaults['list'].length > 0) {
    for (var i = 0; i < beautytips_defaults['list'].length; i++) {
      jQuery.bt.defaults[beautytips_defaults['list'][i]] = beautytips_defaults[beautytips_defaults['list'][i]];
    }
  }
  for (var key in beautytips) {
    // Build array of options that were passed to beautytips_add_beautyips
    var bt_options = new Array();
    if (beautytips[key]['list']) {
      for ( var k = 0; k < beautytips[key]['list'].length; k++) {
        bt_options[beautytips[key]['list'][k]] = beautytips[key][beautytips[key]['list'][k]];
      }
    }
    if (beautytips[key]['text']) {
      $(beautytips[key]['cssSelect']).each(function() {
        $(this).bt(beautytips[key]['text'], bt_options);
      });
    }
    else if (beautytips[key]['ajaxPath']) {
      $(beautytips[key]['cssSelect']).each(function() {
        $(this).bt(bt_options);
      });
    }
    else {
      $(beautytips[key]['cssSelect']).each(function() {
        $(this).bt(bt_options);
      });
    }
    bt_options.length = 0;
  }
  // Add basic beautytips to all elements of class 'beautytips'
  $(".beautytips").bt();
}
