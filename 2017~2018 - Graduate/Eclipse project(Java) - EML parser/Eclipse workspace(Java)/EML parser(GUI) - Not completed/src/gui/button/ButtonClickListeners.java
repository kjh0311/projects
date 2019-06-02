package gui.button;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import actions.ButtonActions;
import program_start.Actions;

final class ButtonClickListeners {
	private ButtonActions button_actions;
	class LoadEmls implements ActionListener {
		public void actionPerformed(ActionEvent arg0)
		{
			button_actions.loadEmls();
		}		
	}
	class LoadSheet implements ActionListener {
		public void actionPerformed(ActionEvent arg0)
		{
			button_actions.loadSheet();
		}		
	}
	class Save implements ActionListener {
		public void actionPerformed(ActionEvent arg0)
		{
			button_actions.save();
		}		
	}
	class SaveAs implements ActionListener {
		public void actionPerformed(ActionEvent arg0)
		{
			button_actions.saveAs();
		}		
	}
	class Clear implements ActionListener {
		public void actionPerformed(ActionEvent arg0)
		{
			button_actions.clear();
		}		
	}
	
	
	final ActionListener
	loadEmls, loadSheet, save, saveAs, clear;
	
	
	
	ButtonClickListeners(ButtonActions button_actions) {
		this.button_actions = button_actions;
		loadEmls = new LoadEmls();
		loadSheet = new LoadSheet();
		save = new Save();
		saveAs = new SaveAs();
		clear = new Clear();		
	}
}
