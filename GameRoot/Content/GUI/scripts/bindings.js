$(function() {
	engine.on('TextChange', function (id, newText) {
    	$(id).text(newText);
	});
});