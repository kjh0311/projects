package program_start;

import data_controller.RangeDataController;
import data_controller.SheetDataController;

public class DataController
{
	
	public final SheetDataController sheet;
	public final RangeDataController range;
	
	public DataController()
	{
		sheet = new SheetDataController();
		range = new RangeDataController();
		sheet.addRangeController(range);
	}



	public void addGuiController(GuiController gui_controller) {
		sheet.addGuiController(gui_controller);
		range.addGuiController(gui_controller.getRangeSpecifyingGuiController());
	}

	
	
}
