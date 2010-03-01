/**
 * jQuery to show on beautytips admin settings page
 */
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

  // Add the color picker to certain textfields
  $('#edit-bt-options-box-fill, #edit-bt-options-box-strokeStyle, #edit-bt-options-box-shadowColor').ColorPicker({
    onSubmit: function(hsb, hex, rgb, el) {
      $(el).val('#' + hex);
      $(el).ColorPickerHide();
    },
    onBeforeShow: function () {
      value = this.value.replace("#", "");
      $(this).ColorPickerSetColor(value);
    }
  })
  .bind('keyup', function(){
    $(this).ColorPickerSetColor(this.value);
  });


  var popupText = "Sed justo nibh, ultrices ut gravida et, laoreet et elit. Nullam consequat lacus et dui dignissim venenatis. Curabitur quis urna eget mi interdum viverra quis eu enim. Ut sit amet nunc augue. Morbi fermentum ultricies velit sed aliquam. Etiam dui tortor, auctor sed tempus ac, auctor sed sapien."
  $("#beautytips-site-wide-popup").bt(popupText, {
    positions: ['right']
  });

  themeSettings = beautytipsGetThemeSettings();
  currentTheme = $("input[name='beautytips_default_style']:checked").val(); 
  $("#beauty-default-styles input").click(function() {
    currentTheme = $("input[name='beautytips_default_style']:checked").val();
  });
  beautytipsAddDefaultBeautytips(themeSettings);

  // TODO: This is still in the experimental stage - the drop shadow is still an issue
  $("#beautytips-popup-changes").click( function() {
    options = beautytipsSetupDefaultOptions(themeSettings[currentTheme]); 
    // General options
    $("#beautytips-site-wide-popup").next('fieldset').find('.fieldset-wrapper').children('.form-item:not(.beautytips-css-styling)').each( function() {
      var name = $(this).find('input').attr('name'); 
      var optionName = name.replace("bt-options-box-", "");
      var newValue = $(this).find('input').val();
      if (optionName == 'shadow') {
        newValue = $(".beautytips-options-shadow input[@name='bt-options-box-shadow']:checked").val();
        newValue = newValue == 'default' ? null : (newValue == 'shadow' ? true : false);
      }
      if (newValue || newValue === false) {
        if (optionName == 'cornerRadius') {
          newValue = Number(newValue);
        }
        options[optionName] = newValue;
      }
    });
    // css options
    $(".beautytips-css-styling").children('.form-item').each( function() {
      var newValue = $(this).find('input').val();
      var name = $(this).find('input').attr('name'); 
      var optionName = name.replace("bt-options-css-", "");
      if (!options['cssStyles']) {
        options['cssStyles'] = new Array();
      }
      if (newValue || newValue === false) {
        options['cssStyles'][optionName] = newValue;
      }
    });
    $(this).bt(popupText, options);
  }); 
}

function beautytipsAddDefaultBeautytips(themeSettings) {
 
  // Beautytips examples shown on Beautytips settings page
  $('#edit-beautytips-default-style-default-wrapper label').bt('This is the default style balloon.', themeSettings['default']);
  $('#edit-beautytips-default-style-netflix').bt('This is the netflix style balloon.', themeSettings['netflix']);
  $('#edit-beautytips-default-style-facebook').bt('This is a facebook style balloon.', themeSettings['facebook']);
  $('#edit-beautytips-default-style-transparent').bt('This balloon is transparent with big white text.', themeSettings['transparent']);
  $('#edit-beautytips-default-style-big-green').bt('This balloon is green with no border and large text.', themeSettings['big_green']);
  $('#edit-beautytips-default-style-google-maps').bt('This is a Google maps styled balloon.', themeSettings['google_maps']); 
  $('#edit-beautytips-default-style-hulu').bt('This is a Hulu styled balloon.', themeSettings['hulu']); 
  return true;
}

function beautytipsSetupDefaultOptions(themeSettings) {
  var options = new Array();
  options = jQuery.bt.defaults;

  for (var key in themeSettings) {
    if (key == 'cssStyles') {
      for (var option in themeSettings['cssStyles']) {
        options['cssStyles'][option] = themeSettings['cssStyles'][option];
      }
    }
    else {
      options[key] = themeSettings[key];
    }
  }
  options['positions'] = 'right';
  options['trigger'] = ['dblclick', 'click'];

  return options;
}

function beautytipsGetThemeSettings() {
  themeSettings = new Array();
  themeSettings['default'] = {
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
  themeSettings['netflix'] = {
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
  themeSettings['facebook'] = {
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
  themeSettings['transparent'] = {
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
  themeSettings['big_green'] = {
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
  themeSettings['google_maps'] = {
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
  themeSettings['hulu'] = {
    positions: ['right'],
    fill: '#F4F4F4',
    strokeStyle: '#666666', 
    strokeWidth: 1,
    spikeLength: 20,
    spikeGirth: 10,
    width: 350,
    shrinkToFit: true,
    overlap: 0,
    centerPointY: 1,
    cornerRadius: 0, 
    cssStyles: {
      fontFamily: '"Lucida Grande",Helvetica,Arial,Verdana,sans-serif', 
      fontSize: '12px',
      padding: '10px 14px'
    },
    shadow: true,
    shadowColor: 'rgba(0,0,0,.5)',
    shadowBlur: 8,
    shadowOffsetX: 4,
    shadowOffsetY: 4
  }
  return themeSettings;
}

