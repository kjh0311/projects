package actions.range_specifying;

import java.util.Calendar;

import data_controller.RangeDataController;
import data_controller.SheetDataController;
import program_start.DataController;

public class RadioButtonActions {
	
	private final SheetDataController sheet_controller;	
	public RadioButtonActions(DataController data_controller) {		
		sheet_controller = data_controller.sheet;
	}	
	
	public void setRangeSpecifyingMode(boolean true_or_false) {
		sheet_controller.setRangeSpecifyingMode(true_or_false);
	}
}
