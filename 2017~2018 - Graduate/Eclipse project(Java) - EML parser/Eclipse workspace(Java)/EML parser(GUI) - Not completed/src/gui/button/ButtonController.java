package gui.button;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Rectangle;
import javax.swing.JButton;
import javax.swing.JLabel;

import actions.ButtonActions;
import program_start.Actions;



public class ButtonController
{
	private Container container;
	private JButton loadEmls, loadSheet, save, saveAs, clear;
	
	
	public void addButtons(Container container)
	{
		this.container = container;
		loadEmls = addButton(ButtonParameters.LOAD_EMLS);
		loadSheet = addButton(ButtonParameters.LOAD_SHEET);
		save = addButton(ButtonParameters.SAVE);
		saveAs = addButton(ButtonParameters.SAVE_AS);
		clear = addButton(ButtonParameters.CLEAR);
	}
	
	
	
	public void addActions(ButtonActions button_actions)
	{
		 ButtonClickListeners listeners;
		 listeners = new ButtonClickListeners(button_actions);
		 loadEmls.addActionListener(listeners.loadEmls);
		 loadSheet.addActionListener(listeners.loadSheet);
		 save.addActionListener(listeners.save);
		 saveAs.addActionListener(listeners.saveAs);
		 clear.addActionListener(listeners.clear);
	}
	
	
	private JButton addButtonCommonSetting(JButton button, ButtonParameters.Data param) {
		
		Rectangle bounds;
		boolean enabled;		
		
		bounds = param.bounds;
		enabled = param.enabled;		
		button.setBounds(bounds);
		button.setEnabled(enabled);		
		
		container.add(button);
		return button;
	}
	
	
	
	private JButton addButton(ButtonParameters.MultiLine param) {
		String[] strings = param.strings;		
		JButton button = new JButton();		
		button.setLayout(new FlowLayout());
		for (int i=0; i<strings.length; i++) {
			Font font;
			JLabel label = new JLabel(strings[i]);
			label.setAlignmentX(JLabel.CENTER);
			font = label.getFont();
			font = font.deriveFont(Font.BOLD);
			label.setFont(font);
			button.add(label);
		}		
		return addButtonCommonSetting(button, param);
	}
	
	private JButton addButton(ButtonParameters.SingleLine param) {
		Font font;
		String string = param.string;
		JButton button = new JButton(string);		
		button.setAlignmentX(JButton.CENTER_ALIGNMENT);
		font = button.getFont();
		font = font.deriveFont(Font.BOLD);
		button.setFont(font);
		return addButtonCommonSetting(button, param);
	}



	public void setEnabledForSaveAndClearButton(boolean true_or_false)
	{
		save.setEnabled(true_or_false);
		saveAs.setEnabled(true_or_false);
		clear.setEnabled(true_or_false);
	}
}

