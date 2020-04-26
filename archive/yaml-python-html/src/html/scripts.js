function toggleLeftMenubar() {
    var e = document.getElementById('leftMenubar');
    if(e.style.display === 'none') {
	e.style.display = 'block';
    } else {
	e.style.display = 'none';
    }
}
