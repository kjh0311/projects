package ui;
import java.awt.Container;

import ui.*;
import ui.gui_controller.*;


public class EmlParserGUI_Tester {
	
	
	public static void main(String args[]) {
		
		new EmlParserGUI_Tester();
		
	}
	
	
	private EmlParserGUI_Tester() {
		EmlParserWindow window; Container container;
		GUI_Controller gui_Controller;		
		
		window = new EmlParserWindow();
		container = window.getContentPane();
		container.setLayout(null);
		
		gui_Controller = new GUI_Controller();
		gui_Controller.addAllGUI_ComponentsTo(container);		
		
		window.setVisible(true);
	}
}




