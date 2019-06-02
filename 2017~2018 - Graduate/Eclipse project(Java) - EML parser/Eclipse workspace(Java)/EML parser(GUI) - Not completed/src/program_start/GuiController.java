package program_start;
import java.awt.Container;
import java.awt.Font;
import java.util.Date;

import gui.*;
import gui.button.ButtonController;
import gui.range_specifying.RangeSpecifyingGuiController;
import gui.state_label_controller.StateLabelController;
import gui.table.TableGuiController;
import gui.window.WindowController;


public class GuiController
{
	

	final WindowController window_controller;
	final TableGuiController table_controller;
	final StateLabelController state_label_controller;
	final ButtonController buttons_controller;
	final RangeSpecifyingGuiController range_specifying_gui_controller;
	
	
	private boolean data_loaded;
	
	
	
	public GuiController()
	{
		window_controller = new WindowController();
		table_controller = new TableGuiController();
		state_label_controller = new StateLabelController();
		buttons_controller = new ButtonController();
		range_specifying_gui_controller = new RangeSpecifyingGuiController();
	}	
	

	public void showInitAll()
	{
		Container container;
		container = window_controller.showWindow();
		table_controller.addTable(container);
		state_label_controller.addLabels(container);
		buttons_controller.addButtons(container);
		range_specifying_gui_controller.addRangeSpecifyingGui(container);		
		
		window_controller.updateWindow();
	}

	public void addActions(Actions actions)
	{
		buttons_controller.addActions(actions.button);
		range_specifying_gui_controller.addActions(actions.range);
	}


	public TableGuiController getTableController() {
		return table_controller;
	}

	
	public RangeSpecifyingGuiController getRangeSpecifyingGuiController() {
		return range_specifying_gui_controller;
	}


	public ButtonController getButtonController()
	{
		return buttons_controller;
	}

	
	
	public void setData(String[][] data, String format, String path)
	{
		table_controller.updateData(data);
		if (data_loaded == false) {
			range_specifying_gui_controller.setRangeSpecifyingEnabled(true);
			buttons_controller.setEnabledForSaveAndClearButton(true);
			data_loaded = true;
		}
		state_label_controller.setText(format, path);
	}
	
	
	public void setSavedFilePath(String file_path) {
		state_label_controller.setText(Strings.FILE_SAVED, file_path);
	}
	
	
	public void clearData()
	{			
		range_specifying_gui_controller.setEnabled(false);
		buttons_controller.setEnabledForSaveAndClearButton(false);
		table_controller.clear(); // 이거 버그 때문에 맨 밑에 둬야함
		state_label_controller.clear();		
		data_loaded = false;
	}	


	public void updateData(String[][] fullData)
	{
		table_controller.updateData(fullData);
		state_label_controller.setRangeAll();
	}
	
	
	public void specifyDataRange(String[][] lookUpData,  boolean using_time_for_range_specifying, Date start, Date end)
	{
		table_controller.updateData(lookUpData);
		state_label_controller.setRange(using_time_for_range_specifying, start, end);
	}


	public void setRangeSpecifyingEnable(boolean true_or_false)
	{
		range_specifying_gui_controller.setRangeSpecifyingMode(true_or_false);
	}


	public void setSpecifyingTimeEnabled(boolean true_or_false)
	{		
		range_specifying_gui_controller.setSpecifyingTimeEnabled(true_or_false);
	}
}




