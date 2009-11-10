Drupal.behaviors.beautytipsAdmin = function() {

  if (!$("#edit-beautytips-always-add").attr("checked")) {
    // Disable input and hide its description.
    $("#edit-beautytips-added-selectors").attr("disabled","disabled");
    $("#edit-beautytips-added-selectors-wrapper").hide(0);
  }
  $("#edit-beautytips-always-add").bind("click", function() {
    if ($("#edit-beautytips-always-add").attr("checked")) {
      // Auto-alias unchecked; enable input.
      $("#edit-beautytips-added-selectors").removeAttr("disabled");
      $("#edit-beautytips-added-selectors-wrapper").slideDown('fast');
    }
    else {
      // Auto-alias checked; disable input.
      $("#edit-beautytips-added-selectors").attr("disabled","disabled");
      $("#edit-beautytips-added-selectors-wrapper").slideUp('fast');
    }
  });

  var popup_test = "Sed justo nibh, ultrices ut gravida et, laoreet et elit. Nullam consequat lacus et dui dignissim venenatis. Curabitur quis urna eget mi interdum viverra quis eu enim. Ut sit amet nunc augue. Morbi fermentum ultricies velit sed aliquam. Etiam dui tortor, auctor sed tempus ac, auctor sed sapien."
  $("#beautytips-site-wide-popup").bt(popup_test, {
    positions: ['right']
  });

  theme_settings = beautytipsGetThemeSettings();

  // TODO: This needs is still in the experimental stage
  $("#beautytips-popup-changes").click( function() {
    var options = new Array();
    options['positions'] = 'right';
    options['trigger'] = ['dblclick', 'mouseout'];
    $("#beautytips-site-wide-popup").next('fieldset').find('.fieldset-wrapper').children('.form-item').each( function() {
      var new_value = $(this).find('input').val();
      //var old_value = $(this).find('input').attr('value'); 
      var name = $(this).find('input').attr('name'); 
      if (name == 'bt-options-shadow') {
        new_value = $(this).find('input').attr("checked") ? true : false;
      }
      if (new_value || new_value === false) {
        var option_name = name.replace("bt-options-", ""); 
        if (option_name == 'cornerRadius') {
          new_value = Number(new_value);
        }
        options[option_name] = new_value;
      }
      /*else { 
        if (theme_settings[current_theme][option_name]) {
          options[option_name] = theme_settings[current_theme][option_name]; 
        }
        else {
          options[option_name] = jQuery.bt.defaults[option_name]; 
          alert(jQuery.bt.defaults[option_name]);
        }
      }*/
    });
    $(this).bt(popup_test, options);
  });
 
  // Beautytips examples shown on Beautytips settings page
  $('#edit-beautytips-default-style-default-wrapper label').bt('This is the default style balloon.', theme_settings['default']);
  $('#edit-beautytips-default-style-netflix').bt('This is the netflix style balloon.', theme_settings['netflix']);
  $('#edit-beautytips-default-style-facebook').bt('This is a facebook style balloon.', theme_settings['facebook']);
  $('#edit-beautytips-default-style-transparent').bt('This balloon is transparent with big white text.', theme_settings['transparent']);
  $('#edit-beautytips-default-style-big-green').bt('This balloon is green with no border and large text.', theme_settings['big_green']);
  $('#edit-beautytips-default-style-google-maps').bt('This is a Google maps styled balloon.', theme_settings['google_maps']); 
}

function beautytipsGetThemeSettings() {
  theme_settings = new Array();
  theme_settings['default'] = {
    positions: ['right'],
    overlap: 0,
    centerPointY: .5,
    centerPointX: .5,
    fill: "rgb(255, 255, 102)", 
    strokeStyle: "#000",
    strokeWidth: 1, 
    spikeLength: 40, 
    spikeGirth: 10, 
    padding: 8, 
    cornerRadius: 10,
    shadow: false, 
    shadowBlur: 3, 
    cssStyles: {}
  } 
  theme_settings['netflix'] = {
    positions: ['right'],
    overlap: -8,
    centerPointY: .1,
    centerPointX: .5, 
    padding: 8, 
    spikeGirth: 10, 
    spikeLength: 50, 
    cornerRadius: 10, 
    fill: '#FFF', 
    strokeStyle: '#B9090B', 
    strokeWidth: 1,
    shadow: true, 
    shadowBlur: 12, 
    shadowColor: "#000",
    cssStyles: {
      fontSize: '12px',
      fontFamily: 'arial,helvetica,sans-serif'
    }
  } 
  theme_settings['facebook'] = {
    positions: ['right'],
    overlap: 0,
    centerPointY: .5,
    centerPointX: .5,
    fill: '#F7F7F7', 
    strokeStyle: '#B7B7B7',
    strokeWidth: 1, 
    spikeLength: 40, 
    spikeGirth: 10, 
    padding: 8, 
    cornerRadius: 0,
    shadow: false, 
    shadowBlur: 3, 
    cssStyles: {
      fontFamily: '"lucida grande",tahoma,verdana,arial,sans-serif', 
      fontSize: '11px'
    }
  }
  theme_settings['transparent'] = {
    positions: ['right'],
    overlap: 0,
    padding: 20,
    width: 120,
    cornerRadius: 10,
    centerPointY: .5,
    centerPointX: .5,
    spikeLength: 40,
    spikeGirth: 20,
    cornerRadius: 40,
    fill: 'rgba(0, 0, 0, .8)',
    strokeStyle: "#000",
    strokeWidth: 3,
    strokeStyle: '#CC0',
    shadow: false, 
    shadowBlur: 3,
    cssStyles: {color: '#FFF', fontWeight: 'bold'}
  }
  theme_settings['big_green'] = {
    positions: ['right'],
    width: 300,
    fill: '#00FF4E',
    overlap: 0,
    centerPointY: .5,
    centerPointX: .5,
    strokeWidth: 0,
    spikeLength: 40,
    spikeGirth: 10,
    padding: 20,
    cornerRadius: 15,
    shadow: false, 
    shadowBlur: 3,
    cssStyles: {
      fontFamily: '"lucida grande",tahoma,verdana,arial,sans-serif', 
      fontSize: '14px'
    }
  }
  theme_settings['google_maps'] = {
    positions: 'top',
    width: 220,
    overlap: 0,
    centerPointY: .5,
    centerPointX: .9,
    spikeLength: 65,
    spikeGirth: 40,
    padding: 15,
    cornerRadius: 25,
    shadow: false, 
    shadowBlur: 3,
    fill: '#FFF',
    strokeStyle: '#ABABAB',
    strokeWidth: 1,
    cssStyles: {color: 'black',}
  }
  return theme_settings;
}


