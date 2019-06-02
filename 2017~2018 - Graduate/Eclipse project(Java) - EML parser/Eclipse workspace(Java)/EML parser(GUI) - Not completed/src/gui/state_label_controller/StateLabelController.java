package gui.state_label_controller;

import java.awt.Container;
import java.awt.Font;
import java.awt.Rectangle;
import java.lang.reflect.Array;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.JLabel;

import gui.Bounds;
import gui.JMultilineLabel;
import gui.Strings;

public class StateLabelController
{
	private Container container;
	private JMultilineLabel state_label;
	private JLabel range_label;
	
	
	public void addLabels(Container container)
	{
		this.container = container;
		state_label = addStateLabel();
		range_label = addRangeLabel();
	}
	
	
	private JMultilineLabel addStateLabel()
	{
		JMultilineLabel label;
		label = new JMultilineLabel(Strings.INIT_STATE);
		label.setBounds(Bounds.STATE_LABEL);
		container.add(label);
		return label;
	}
	
	
	private JLabel addRangeLabel()
	{
		JLabel label;
		Font font;
		label = new JLabel();
		label.setBounds(Bounds.RANGE_LABEL);
		
		font = label.getFont();
		font = font.deriveFont(Font.BOLD);
		label.setFont(font);
		
		container.add(label);
		return label;
	}
	
	/*
	public void setText(String string) {
		state_label.setText(string);
	}
	*/
	
	public void setText(String format, Object ...format_args){
		String string;		
		string = String.format(format, format_args);
		state_label.setText(string);
	}
	
	
	public void setRangeAll() {
		range_label.setText(Strings.RANGE_ALL);
	}
	
	
	private class TransformedDates {
		String start, end;
	}


	public void setRange(boolean using_time_for_range_specifying, Date start, Date end)
	{
		
		String string;
		TransformedDates t;
		t = transform_dates(using_time_for_range_specifying, start, end);
		string = String.format(Strings.RANGE_LOOK_UP, t.start, t.end);
		range_label.setText(string);
	}
	
	
	private TransformedDates transform_dates(boolean using_time_for_range_specifying, Date start, Date end) {
		TransformedDates t;
		t = new TransformedDates();

		if (using_time_for_range_specifying) {
			t.start = transform_date(start, Strings.LABEL_DATE_TIME_FORMAT);
			t.end = transform_date(end, Strings.LABEL_DATE_TIME_FORMAT);
		} else {
			t.start = transform_date(start, Strings.LABEL_DATE_FORMAT);
			t.end = transform_date(end, Strings.LABEL_DATE_FORMAT);
		}
		
		return t;
	}
	
	
	private String transform_date(Date date, String format) {
		String string;
		SimpleDateFormat formatter;
		
		formatter = new SimpleDateFormat(format);		
		string = formatter.format(date);
		
		return string;
	}
	
	
	public void clear() {
		state_label.setText(Strings.INIT_STATE);
		range_label.setText("");
	}
}
