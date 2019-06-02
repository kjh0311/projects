package ui.gui_controller.button;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.Rectangle;

import javax.swing.JButton;
import javax.swing.JLabel;




public class ButtonGUI_Controller
{	
	private Container container;
	private JButton loadEmls, loadSheet, save, saveAs, clear;
	
	
	public void addButtonsTo(Container container)
	{
		this.container = container;
		loadEmls = addButton(ButtonParameters.LOAD_EMLS);
		loadSheet = addButton(ButtonParameters.LOAD_SHEET);
		save = addButton(ButtonParameters.SAVE);
		saveAs = addButton(ButtonParameters.SAVE_AS);
		clear = addButton(ButtonParameters.CLEAR);
	}
	
	
	private JButton addButton(ButtonParameters.MultiLine param) {
		String[] strings = param.strings;
		Rectangle bounds = param.bounds;
		JButton button = new JButton();		
		button.setBounds(bounds);
		button.setLayout(new FlowLayout());
		for (int i=0; i<strings.length; i++) {
			JLabel label = new JLabel(strings[i]);
			label.setAlignmentX(JLabel.CENTER);
			button.add(label);
		}		
		container.add(button);
		return button;
	}
	
	private JButton addButton(ButtonParameters.SingleLine param) {
		String string = param.string;
		Rectangle bounds = param.bounds;
		JButton button = new JButton(string);
		
		button.setBounds(bounds);
		button.setAlignmentX(JButton.CENTER_ALIGNMENT);
		container.add(button);
		return button;
	}	
}






