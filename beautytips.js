Drupal.behaviors.beautytips = function() {
    jQuery.bt.defaults.closeWhenOthersOpen = true;
    for (var key in Drupal.settings.beautytips) {
      if (!Drupal.settings.beautytips[key]['additionalJavascript']) {
	      if (Drupal.settings.beautytips[key]['ajaxPath']) {
          $(Drupal.settings.beautytips[key]['area']).each(function() {
            $(this).bt({
              trigger:  Drupal.settings.beautytips[key]['trigger'],
              ajaxPath: $(this).attr('href') + Drupal.settings.beautytips[key]['ajaxPath'],
              width: Drupal.settings.beautytips[key]['width'],
            });
          });
        }
        else {
          $(Drupal.settings.beautytips[key]['area']).each(function() {
            $(this).bt({
              trigger:  Drupal.settings.beautytips[key]['trigger'],
              contentSelector: Drupal.settings.beautytips[key]['contentSelector'],
              width: Drupal.settings.beautytips[key]['width'],
            });
          });
        }
      }
    }
}