package ui.gui_controller.specifyRange;
import java.awt.Container;
import javax.swing.JLabel;

import ui.Bounds;
import ui.Strings;
import ui.gui_controller.specifyRange.dateAndTime.*;
import ui.gui_controller.specifyRange.pushButtonForLookUp.PushButtonForLookUpGuiController;
import ui.gui_controller.specifyRange.radioButton.RadioButtonGuiController;



public class SpecifyRangeGUI_Controller
{
	private RadioButtonGuiController radioButtonController;
	private PushButtonForLookUpGuiController pushButtonController;
	private DateAndTimeSetterGuiController dateAndTimeSetterController;	
	public SpecifyRangeGUI_Controller()
	{
		radioButtonController = new RadioButtonGuiController();
		pushButtonController = new PushButtonForLookUpGuiController();
		dateAndTimeSetterController = new DateAndTimeSetterGuiController();
	}	

	
	
	public void addSpecifyRangeTo(Container container)
	{
		addTitleTo(container);
		radioButtonController.addRadioButtonsTo(container);
		pushButtonController.addPushButtonsTo(container);
		dateAndTimeSetterController.addDateAndTimeSetterTo(container);
	}
	
	
	private void addTitleTo(Container container) {
		JLabel label;
		label = new JLabel(Strings.SPECIFY_RANGE);
		label.setBounds(Bounds.SpecifyRange.TITLE);
		container.add(label);		
	}
}



