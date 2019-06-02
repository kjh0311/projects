package actions.range_specifying;

import java.util.Calendar;

import actions.file.FileLoader;
import actions.file.FileSaver;
import data_controller.RangeDataController;
import data_controller.SheetDataController;
import program_start.DataController;

public class TimeSpecifyingAllowActions {
	
	private final SheetDataController sheet_controller;	
	public TimeSpecifyingAllowActions(DataController data_controller) {		
		sheet_controller = data_controller.sheet;
	}

	public void set_using_time_for_range_specifying(boolean true_or_false) {
		sheet_controller.set_using_time_for_range_specifying(true_or_false);
	}
}
