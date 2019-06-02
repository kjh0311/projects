package ui.gui_controller.specifyRange.radioButton;
import java.awt.Container;
import java.awt.Rectangle;

import javax.swing.ButtonGroup;
import javax.swing.JRadioButton;

import ui.Bounds;
import ui.Strings;


public class RadioButtonGuiController
{	
	public void addRadioButtonsTo(Container container)
	{
		ButtonGroup group;
		group = new ButtonGroup();	
		addRadioButton(Parameters.ALL, group, container);
		addRadioButton(Parameters.RANGE, group, container);
	}
	
	
	private void addRadioButton(Parameters.Data data, ButtonGroup group, Container container) {
		JRadioButton rb;		
		rb = new JRadioButton(data.string);
		rb.setSelected(data.checked);
		rb.setBounds(data.bounds);		
		group.add(rb);
		container.add(rb);
	}
}




