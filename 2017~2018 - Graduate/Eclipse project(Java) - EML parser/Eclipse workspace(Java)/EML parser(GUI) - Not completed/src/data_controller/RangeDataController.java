package data_controller;

import java.util.Calendar;

import gui.range_specifying.RangeSpecifyingGuiController;
import gui.range_specifying.dateAndTime.DateAndTimeSetterGuiController;

public class RangeDataController
{
	private RangeSpecifyingGuiController gui_controller;
	private DateAndTimeSetterGuiController dateAndTimeSetterGuiController;
	
	
	//private SpinnerCommonDateModel common_start_model, common_end_model;
	private Calendar start_calendar, end_calendar;


	public void addGuiController(RangeSpecifyingGuiController rangeSpecifyingGuiController) {
		gui_controller = rangeSpecifyingGuiController;
		dateAndTimeSetterGuiController = gui_controller.getDateAndTimeSetterController();
		
		start_calendar = zeroTimeTodayCalendar();
		end_calendar = zeroTimeTodayCalendar();
		
		dateAndTimeSetterGuiController.setStartAndEndCalendar(start_calendar, end_calendar);
	}
	
	
	private Calendar zeroTimeTodayCalendar() {		
		Calendar today_calendar;		
		today_calendar = Calendar.getInstance();		
		return createZeroTimeCalendar(today_calendar);
	}	
	
	public Calendar getZeroTimeStartCalendar() {
		return createZeroTimeCalendar(start_calendar);
	}	
	
	public Calendar getZeroTimeEndCalendar() {
		return createZeroTimeCalendar(end_calendar);
	}
	
	
	
	public Calendar createZeroTimeCalendar(Calendar source_calendar) {
		int year, month, date;
		Calendar new_calendar;		
		
		
		year = source_calendar.get(Calendar.YEAR);
		month = source_calendar.get(Calendar.MONTH);
		date = source_calendar.get(Calendar.DATE); 
		
		new_calendar = Calendar.getInstance();
		//new_calendar.setTimeInMillis(0);
		new_calendar.set(year, month, date, 0, 0, 0);
		return new_calendar;
	}
	

	public Calendar getStartCalendar()
	{
		return start_calendar;
	}	
	
	public Calendar getEndCalendar()
	{
		return end_calendar;
	}	
}