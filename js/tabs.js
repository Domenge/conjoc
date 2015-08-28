var tabLinks = new Array();
var contentDivs = new Array();

function init(index) {

      // Grab the tab links and content divs from the page
      var tabListItems = document.getElementById('tabs').childNodes;
      for ( var i = 0; i < tabListItems.length; i++ ) {
        if ( tabListItems[i].nodeName == "LI" ) {
          var tabLink = getFirstChildWithTagName( tabListItems[i], 'A' );
          var id = getHash( tabLink.getAttribute('href') );
          tabLinks[id] = tabLink;
          contentDivs[id] = document.getElementById( id );
        }
      }

      // Assign onclick events to the tab links, and
      // highlight the first tab
      var i = 0;

      for ( var id in tabLinks ) {
        tabLinks[id].onclick = showTab;
        tabLinks[id].onfocus = function() { this.blur() };
        if ( i == index ) tabLinks[id].className = 'selected';
        i++;
      }

      // Hide all content divs except the first
      var i = 0;

      for ( var id in contentDivs ) {
        if ( i != index ) contentDivs[id].className = 'tabContent hide';
        i++;
      }
}
    
function showTab() {
      var selectedId = getHash( this.getAttribute('href') );

      // Highlight the selected tab, and dim all others.
      // Also show the selected content div, and hide all others.
      for ( var id in contentDivs ) {
        if ( id == selectedId ) {
          tabLinks[id].className = 'selected';
          contentDivs[id].className = 'tabContent';
        } else {
          tabLinks[id].className = '';
          contentDivs[id].className = 'tabContent hide';
        }
      }

      // Stop the browser following the link
      return false;
}

function getFirstChildWithTagName( element, tagName ) {
      for ( var i = 0; i < element.childNodes.length; i++ ) {
        if ( element.childNodes[i].nodeName == tagName ) return element.childNodes[i];
      }
}


function getHash( url ) {
	var hashPos = url.lastIndexOf ( '#' );
	return url.substring( hashPos + 1 );
}

function setVisible(classname,visible){
  var elements = document.getElementsByClassName(classname);

  if(visible){	
    for (var i = 0; i < elements.length;i++){
	elements[i].style.visibility = 'visible';
    }
   }else{
    for (var i = 0; i < elements.length;i++){
	elements[i].style.visibility = 'hidden';
    }   
   }
}

function applyN() {
	
	setVisible("North", 1);
	setVisible("SouthWest", 0);
	setVisible("East", 0);
	setVisible("Central", 0);
}

function applySW(  ) {

	setVisible("North", 0);
	setVisible("SouthWest", 1);
	setVisible("East", 0);
	setVisible("Central", 0);
}

function applyE(  ) {
	setVisible("North", 0);
	setVisible("SouthWest", 0);
	setVisible("East", 1);
	setVisible("Central", 0);
}

function applyCentral(  ) {
	setVisible("North", 0);
	setVisible("SouthWest", 0);
	setVisible("East", 0);
	setVisible("Central", 1);
}
