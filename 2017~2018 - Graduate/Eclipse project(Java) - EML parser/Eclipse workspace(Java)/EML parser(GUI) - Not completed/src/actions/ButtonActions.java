package actions;

import actions.file.FileLoader;
import actions.file.FileSaver;
import data_controller.SheetDataController;

public class ButtonActions {
	private final FileLoader file_loader;
	private final FileSaver file_saver;
	private final SheetDataController sheet_controller;
	
	
	public ButtonActions(SheetDataController sheet_data_controller)
	{		
		sheet_controller = sheet_data_controller;
		file_loader = new FileLoader();
		file_saver = new FileSaver();
	}
	
	
	public void loadEmls()
	{
		file_loader.loadEmls(sheet_controller);
	}
	
	
	public void loadSheet()
	{
		file_loader.loadSheet(sheet_controller);
	}
	
	
	public void save() 
	{
		file_saver.save(sheet_controller);
	}
	
	
	public void saveAs() 
	{
		file_saver.saveAs(sheet_controller);
	}
	
	
	public void clear() 
	{
		sheet_controller.clear();
	}
}
