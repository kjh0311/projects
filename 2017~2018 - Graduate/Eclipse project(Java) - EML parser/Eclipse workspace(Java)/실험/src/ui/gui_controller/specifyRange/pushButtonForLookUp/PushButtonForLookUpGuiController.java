package ui.gui_controller.specifyRange.pushButtonForLookUp;
import java.awt.Container;
import javax.swing.JButton;

import ui.Bounds;
import ui.Strings;



public class PushButtonForLookUpGuiController
{	
	public void addPushButtonsTo(Container container)
	{
		JButton button;
		button = new JButton(Strings.LOOK_UP);
		button.setBounds(Bounds.SpecifyRange.LOOK_UP);
		container.add(button);
	}	
}




