package program_start;
import java.util.Calendar;

import actions.*;
import actions.file.FileLoader;
import actions.file.FileSaver;
import data_controller.RangeDataController;
import data_controller.SheetDataController;



public class Actions
{		
	final ButtonActions button;
	final RangeSpecifyingActions range;	
	public Actions(DataController data_controller)
	{		
		button = new ButtonActions(data_controller.sheet);
		range = new RangeSpecifyingActions(data_controller);
	}
}
