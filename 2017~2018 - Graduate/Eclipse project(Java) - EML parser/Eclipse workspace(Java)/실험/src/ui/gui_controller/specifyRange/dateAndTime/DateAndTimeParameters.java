package ui.gui_controller.specifyRange.dateAndTime;

import java.awt.Rectangle;
import java.util.Calendar;

import ui.Bounds;
import ui.Strings;

class DateAndTimeParameters {
	
	
	static class LabelParameters {
		final String string;
		Rectangle bounds;
		LabelParameters(String string) {
			this.string = string;
		}
	}	
	static class SpinnerParameters {
		Rectangle bounds;
		// 아래 둘은 공통항목
		final String format;
		final int[] fields;
		SpinnerParameters(String format, int[] fields) {
			this.format = format;
			this.fields = fields;
		}
	}
	
	
	private static final class Formats {
		static final String
			YEAR = "yyyy",
			MONTH = "MM",
			DATE = "dd",
			TIME = "a  hh:mm";
	}	
	private static final class CalendarFields {
		static final int[] 
			YEAR = {Calendar.YEAR},
			MONTH = {Calendar.MONTH},
			DATE = {Calendar.DATE},
			TIME = {Calendar.AM_PM, Calendar.HOUR, Calendar.MINUTE};
	}
	
	
	static abstract class StartOrEnd {
		static class AllSpinnerParameters {
			SpinnerParameters year, month, date, time;
			AllSpinnerParameters() {
				year = new SpinnerParameters(Formats.YEAR, CalendarFields.YEAR);
				month = new SpinnerParameters(Formats.MONTH, CalendarFields.MONTH);
				date = new SpinnerParameters(Formats.DATE, CalendarFields.DATE);
				time = new SpinnerParameters(Formats.TIME, CalendarFields.TIME);
			}
		}
		static class AllLabelParameters {
			LabelParameters year, month, date;
			AllLabelParameters() {
				year = new LabelParameters(Strings.YEAR);
				month = new LabelParameters(Strings.MONTH);
				date = new LabelParameters(Strings.DAY);
			}
		}
		
		LabelParameters title;
		AllSpinnerParameters spinners;
		AllLabelParameters labels;
		StartOrEnd() {			
			spinners = new AllSpinnerParameters();
			labels = new AllLabelParameters();
		}
	}
	
	
	class Start extends StartOrEnd {
		Start() {
			title = new LabelParameters(Strings.START);
			title.bounds = Bounds.SpecifyRange.START.title;
			
			spinners.year.bounds = Bounds.SpecifyRange.START.spinner.year;
			spinners.month.bounds = Bounds.SpecifyRange.START.spinner.month;
			spinners.date.bounds = Bounds.SpecifyRange.START.spinner.date;
			spinners.time.bounds = Bounds.SpecifyRange.START.spinner.time;
			
			labels.year.bounds = Bounds.SpecifyRange.START.label.year;
			labels.month.bounds = Bounds.SpecifyRange.START.label.month;
			labels.date.bounds = Bounds.SpecifyRange.START.label.date;
		}
	}
	class End extends StartOrEnd {
		End() {
			title = new LabelParameters(Strings.END);
			title.bounds = Bounds.SpecifyRange.END.title;

			spinners.year.bounds = Bounds.SpecifyRange.END.spinner.year;
			spinners.month.bounds = Bounds.SpecifyRange.END.spinner.month;
			spinners.date.bounds = Bounds.SpecifyRange.END.spinner.date;
			spinners.time.bounds = Bounds.SpecifyRange.END.spinner.time;
			
			labels.year.bounds = Bounds.SpecifyRange.END.label.year;
			labels.month.bounds = Bounds.SpecifyRange.END.label.month;
			labels.date.bounds = Bounds.SpecifyRange.END.label.date;
		}
	}
	
	final StartOrEnd START, END;
	DateAndTimeParameters() {
		START = new Start();
		END = new End();
	}
}