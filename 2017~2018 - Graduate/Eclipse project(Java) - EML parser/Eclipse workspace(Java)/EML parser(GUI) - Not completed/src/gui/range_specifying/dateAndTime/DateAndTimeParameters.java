package gui.range_specifying.dateAndTime;

import java.awt.Rectangle;
import java.util.Calendar;

import javax.swing.JSpinner;

import gui.Bounds;
import gui.Strings;

class DateAndTimeParameters {
	
	
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
	
	
	
	static class LabelParameters {
		final String string;
		Rectangle bounds;
		LabelParameters(String string) {
			this.string = string;
		}
	}
	
	
	static class SpinnerCommon {
		SpinnerCommonDateModel model;
	}
	
	static class SpinnerParameters {
		final SpinnerCommon COMMON;
		Rectangle bounds;
		final String FORMAT;
		final int[] FIELDS;
		public SpinnerParameters(SpinnerCommon COMMON, String FORMAT, int[] FIELDS) {
			this.COMMON = COMMON;
			this.FORMAT = FORMAT;
			this.FIELDS = FIELDS;
		}

			
	}
	
	
	
	static abstract class StartOrEnd {
		static class AllSpinnerParameters {			
			SpinnerCommon common;
			SpinnerParameters year, month, date, time;
			AllSpinnerParameters() {
				common = new SpinnerCommon();
				year = new SpinnerParameters(common, Formats.YEAR, CalendarFields.YEAR);
				month = new SpinnerParameters(common, Formats.MONTH, CalendarFields.MONTH);
				date = new SpinnerParameters(common, Formats.DATE, CalendarFields.DATE);
				time = new SpinnerParameters(common, Formats.TIME, CalendarFields.TIME);
			}
		}
		static class AllLabelParameters {
			final LabelParameters title, year, month, date;
			AllLabelParameters(String string_title) {
				title = new LabelParameters(string_title);
				year = new LabelParameters(Strings.YEAR);
				month = new LabelParameters(Strings.MONTH);
				date = new LabelParameters(Strings.DAY);
			}
		}		
		
		final AllSpinnerParameters spinners;
		final AllLabelParameters labels;
		StartOrEnd(String string_title) {			
			spinners = new AllSpinnerParameters();
			labels = new AllLabelParameters(string_title);
		}
	}
	
	
	static final class Start extends StartOrEnd {
		Start() {
			super(Strings.START);
			
			
			spinners.year.bounds = Bounds.SpecifyRange.START.spinner.year;
			spinners.month.bounds = Bounds.SpecifyRange.START.spinner.month;
			spinners.date.bounds = Bounds.SpecifyRange.START.spinner.date;
			spinners.time.bounds = Bounds.SpecifyRange.START.spinner.time;
			
			labels.title.bounds = Bounds.SpecifyRange.START.title;
			labels.year.bounds = Bounds.SpecifyRange.START.label.year;
			labels.month.bounds = Bounds.SpecifyRange.START.label.month;
			labels.date.bounds = Bounds.SpecifyRange.START.label.date;
		}
	}
	static final class End extends StartOrEnd {
		End() {
			super(Strings.END);
			labels.title.bounds = Bounds.SpecifyRange.END.title;

			spinners.year.bounds = Bounds.SpecifyRange.END.spinner.year;
			spinners.month.bounds = Bounds.SpecifyRange.END.spinner.month;
			spinners.date.bounds = Bounds.SpecifyRange.END.spinner.date;
			spinners.time.bounds = Bounds.SpecifyRange.END.spinner.time;
			
			labels.year.bounds = Bounds.SpecifyRange.END.label.year;
			labels.month.bounds = Bounds.SpecifyRange.END.label.month;
			labels.date.bounds = Bounds.SpecifyRange.END.label.date;
		}
	}
	
	static final StartOrEnd START, END;
	static {
		START = new Start();
		END = new End();
	}
}