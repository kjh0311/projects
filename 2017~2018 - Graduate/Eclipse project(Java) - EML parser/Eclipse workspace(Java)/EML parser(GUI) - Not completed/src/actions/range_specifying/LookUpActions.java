package actions.range_specifying;

import java.util.Calendar;

import actions.file.FileLoader;
import actions.file.FileSaver;
import data_controller.RangeDataController;
import data_controller.SheetDataController;
import program_start.DataController;

public class LookUpActions {
	
	private final SheetDataController sheet_controller;
	private final RangeDataController range_controller;
	
	
	public LookUpActions(DataController data_controller)
	{		
		sheet_controller = data_controller.sheet;
		range_controller = data_controller.range;
	}
	
	
	public void lookUp()
	{
		Calendar start, end;
		
		start = range_controller.getStartCalendar();
		end = range_controller.getEndCalendar();
		
		sheet_controller.lookUpForSpecifiedRange(start, end);
	}
}
