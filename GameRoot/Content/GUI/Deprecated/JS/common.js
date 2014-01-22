// Style Change Event
(function() {
    var ev = new $.Event('onStyleChange'),
        orig = $.fn.css;
    $.fn.css = function() {
        var ret = orig.apply(this, arguments);
        $(this).trigger(ev);
        return ret; // must include this
    }
})();

$(function() {
    // All Buttons
    $("button").button();
    
    // All Common Windows
    $(".ui-fixed-dialog").dialog({
        dialogClass: "ui-noclose",
        resizable: false,
        draggable: false
    });
});