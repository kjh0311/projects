package data_controller;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.Calendar;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.Vector;

import actions.file.EmlFileExtractor;
import actions.file.SheetFileReader;
import gui.Strings;
import gui.button.ButtonController;
import gui.range_specifying.RangeSpecifyingGuiController;
import gui.table.TableGuiController;
import program_start.GuiController;

public class SheetDataController
{	
	
	private GuiController gui_controller;
	private RangeDataController range_controller;
	
	
	private int 
	FILE_NAME = 0, YEAR = 1, MONTH = 2, DATE = 3, TIME = 4, DATA1 = 5,
	NUMBER_OF_COLUMNS = 6;
	
	
	// 데이터는 아래와 같이 두 가지 형태로 동시에 제공함
	// 즉, 메모리를 두 배로 쓰는 구조라고 보면 됨
	private class Data implements Cloneable {
		String array2d[][], string;
		Data() {
			array2d = null;
			string = null;
		}
		public void copy(Data look_up_data)
		{
			look_up_data.array2d = array2d;
			look_up_data.string = string;
		}
	}
	
	private class FullAndLookUpData {
		Data full, look_up;
		FullAndLookUpData() {
			full = new Data();
			look_up = new Data();
		}
	}
	
	
	private class StartAndEndDate {
		Date start, end;
	}
	
	
	// 로드된 전체 데이터와 
	private FullAndLookUpData data;
	private StartAndEndDate date;
	private File loadedSheetFile;

	private boolean range_specifying_mode;
	private boolean range_specified;
	private boolean using_time_for_range_specifying;	
	
	
	public SheetDataController() {
		data = new FullAndLookUpData();
		date = new StartAndEndDate();
		loadedSheetFile = null;
		range_specifying_mode = false;
		range_specified = false;
		using_time_for_range_specifying = false;
	}
	
	
	public void addGuiController(GuiController gui_controller) {
		this.gui_controller = gui_controller;
	}
	
	

	public void clear() {
		// GUI 클리어
		gui_controller.clearData();
		data = new FullAndLookUpData();
		loadedSheetFile = null;
	}
	
	
	
	public void setLoadedSheetFile(File loadedSheetFile) {
		this.loadedSheetFile = loadedSheetFile;
	}
	
	
	
	public File getLoadedSheetFile() {
		return loadedSheetFile;
	}
	

	public void lookUpForSpecifiedRange(Calendar start, Calendar end)
	{
		int startIndex, endIndex;
		StringBuilder builder;
		int j, size;
		String line, array_line[];
		
		
		sort();
		
		
		startIndex = find_start_index_by_calendar(start);			// 부합하는 첫 인덱스
		endIndex = find_end_index_by_calendar(startIndex, end);		// 부합하지 않는 첫 인덱스가 되어야함
		
		
		builder = new StringBuilder();

		j = 0;
		size = endIndex - startIndex;
		data.look_up.array2d = new String[size][NUMBER_OF_COLUMNS];
		
		for (int i=startIndex; i<endIndex; i++)
		{			
			array_line = data.full.array2d[i];			
			line = String.join(",", array_line);
			builder.append(line+"\n");			
			data.look_up.array2d[j] = array_line; // 전체 결과 내에서 검색
			j++;
		}
		
		data.look_up.string = builder.toString();
		date.start = start.getTime();
		date.end = end.getTime();
		range_specified = true;
		gui_controller.specifyDataRange(data.look_up.array2d, using_time_for_range_specifying, date.start, date.end);
	}
	
	
	// calendar의 값을 넘는 첫 항목의 인덱스임.
	// 넘는 항목이 없다면, 배열의 사이즈를 리턴함.
	private int find_start_index_by_calendar(Calendar start) {		
		return find_index_by_calendar(0, start);
	}
	
	
	private int find_end_index_by_calendar(int startIndex, Calendar end) {
		int return_value, last_field;
		
		if (using_time_for_range_specifying) {
			last_field = Calendar.MINUTE;
		} else {
			last_field = Calendar.DATE;
		}
		
		end.add(last_field, 1);
		return_value = find_index_by_calendar(startIndex, end);
		end.add(last_field, -1);
		return return_value;
	}
	
	
	private int find_index_by_calendar(int startIndex, Calendar base_calendar) {
		int i;		
		Calendar new_calendar;
		String array2d_data[][];		
		
		array2d_data = data.full.array2d;
		for (i=startIndex; i<array2d_data.length; i++)
		{
			new_calendar = array_row_to_calendar(array2d_data[i]);				
			if (new_calendar == null)
			{
				continue;
			}
			else
			{				
				if (using_time_for_range_specifying==false)
				{										
					base_calendar = range_controller.createZeroTimeCalendar(base_calendar);
				}			
				
				if (new_calendar.compareTo(base_calendar) >= 0)
				{
					break;
				}				
			}
		}	
		return i;
	}	
	
	
	private Calendar array_row_to_calendar(String[] array_row)
	{
		Calendar new_calendar;
		int year, month, date;
		int hour_of_day = 0, minute = 0;
		new_calendar = Calendar.getInstance();		
		try
		{
			year = Integer.parseInt(array_row[YEAR]);
			month = Integer.parseInt(array_row[MONTH]);
			date = Integer.parseInt(array_row[DATE]);
			
			new_calendar.set(Calendar.YEAR, year);
			// 월은 -1을 붙혀야 한다는 번거로움이 있음.
			new_calendar.set(Calendar.MONTH, month-1);
			new_calendar.set(Calendar.DATE, date);			
			if ( using_time_for_range_specifying ) {
				String formatted_time, spitted[];				
				formatted_time = array_row[TIME];
				spitted = formatted_time.split(":");				
				hour_of_day = Integer.parseInt(spitted[0]);				
				minute = Integer.parseInt(spitted[1]);				
			}
			new_calendar.set(Calendar.HOUR_OF_DAY, hour_of_day);
			new_calendar.set(Calendar.MINUTE, minute);
			
			return new_calendar;
		}
		catch (Exception e)
		{
			//System.out.println(hour_of_day);
			return null;
		}
	}


	private void sort() {
		
	}
	
	
	
	class ExtensionFilter implements FilenameFilter{

		private String extend;
		public ExtensionFilter(String extend){
			this.extend = extend;
		}

		@Override
		public boolean accept(File dir, String name) { 
			return name.endsWith(extend);
		}
	}
	


	public void loadEmls(File dir_of_eml_files)
	{
		int size; File files[], file;
		EmlFileExtractor extractor;
		String line, row[];
		StringBuilder bulider;
		
		
		extractor = new EmlFileExtractor();
		bulider = new StringBuilder();
		files = dir_of_eml_files.listFiles(new ExtensionFilter(".eml"));
		if (files == null || files.length == 0) {
			return;
		}
		size = files.length;
		data.full.array2d = new String[size][NUMBER_OF_COLUMNS];
		
		
		for (int i=0; i<size; i++)
		{
			file = files[i];
			line = extractor.extractEmlFile(file);
			bulider.append(line+"\n");
			row = line.split(",");
			data.full.array2d[i] = row;
		}
		data.full.string = bulider.toString();
		data.full.copy(data.look_up);
		gui_controller.setData(data.look_up.array2d, Strings.FOLDER_LOADED, dir_of_eml_files.getAbsolutePath());
		setLoadedSheetFile(null);
	}
	
	


	public void loadSheet(File sheet_file)
	{
		int size;
		String line, file_string;
		String[] row, lines;
		SheetFileReader reader;				
		
		
		reader = new SheetFileReader();
		file_string = reader.read(sheet_file);		
		// 맨위에 헤더를 제거함
		data.full.string = file_string.substring(file_string.indexOf("\n")+1);
		lines = data.full.string.split("\n");
		
		size = lines.length;
		data.full.array2d = new String[size][NUMBER_OF_COLUMNS];		
		
		for (int i=0; i<size; i++)
		{
			line = lines[i];
			row = line.split(",");			
			data.full.array2d[i] = row;
		}
		
		data.full.copy(data.look_up);
		
		gui_controller.setData(data.look_up.array2d, Strings.FILE_LOADED, sheet_file.getAbsolutePath());
		setLoadedSheetFile(sheet_file);
		//rangeSpecifyingGuiController.setEnabled(true);
	}


	public String getStringData() {
		if (range_specifying_mode) {
			return data.look_up.string;
		} else {
			return data.full.string;
		}
	}


	public void setRangeSpecifyingMode(boolean true_or_false)
	{
		range_specifying_mode = true_or_false;
		gui_controller.setRangeSpecifyingEnable(true_or_false);
		
		if (range_specifying_mode && range_specified) {
			gui_controller.specifyDataRange(data.look_up.array2d, using_time_for_range_specifying, date.start, date.end);
		} else {
			gui_controller.updateData(data.full.array2d);
		}
		
	}


	public void set_using_time_for_range_specifying(boolean true_or_false)
	{
		using_time_for_range_specifying = true_or_false;
		gui_controller.setSpecifyingTimeEnabled(true_or_false);	
	}


	public void addRangeController(RangeDataController range)
	{
		range_controller = range;
	}


	public void save()
	{
		final String 
		UTF8_BOM = "\uFEFF",
		COLUMN_HEADER = "파일 이름,연도,월,일,시간,데이터1\n";
		String data;
		BufferedWriter writer;
		
		try {
			writer = new BufferedWriter(new FileWriter(loadedSheetFile));			
			data = getStringData();
			writer.write(UTF8_BOM+COLUMN_HEADER);
			writer.write(data);
			writer.close();
			gui_controller.setSavedFilePath(loadedSheetFile.getAbsolutePath());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
