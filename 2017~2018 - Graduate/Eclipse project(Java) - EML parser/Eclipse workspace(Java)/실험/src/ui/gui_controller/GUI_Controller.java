package ui.gui_controller;
import java.awt.Container;

import ui.gui_controller.button.ButtonGUI_Controller;
import ui.gui_controller.specifyRange.SpecifyRangeGUI_Controller;
import ui.gui_controller.table.*;




public class GUI_Controller
{
	private TableGUI_Controller			tableController;
	private ButtonGUI_Controller		buttonController;
	private SpecifyRangeGUI_Controller	specifyRangeController;
	
	
	public GUI_Controller()
	{
		tableController					= new TableGUI_Controller();
		buttonController				= new ButtonGUI_Controller();
		specifyRangeController			= new SpecifyRangeGUI_Controller();
	}
	
	
	public void addAllGUI_ComponentsTo(Container container)
	{
		tableController.addTableTo(container);
		buttonController.addButtonsTo(container);
		specifyRangeController.addSpecifyRangeTo(container);
	}	
}



