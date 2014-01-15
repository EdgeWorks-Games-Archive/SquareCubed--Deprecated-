$(function() {
	engine.on('LabelTextChanged', function (id, newText) {
    	$(id).text(newText);
	});
});