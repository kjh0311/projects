package ui.gui_controller.specifyRange.dateAndTime;
import java.awt.Container;
import java.awt.Rectangle;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.text.ParseException;

import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JSpinner;
import javax.swing.text.DateFormatter;

import ui.Bounds;
import ui.Strings;
import ui.gui_controller.specifyRange.dateAndTime.DateAndTimeParameters.StartOrEnd.AllLabelParameters;
import ui.gui_controller.specifyRange.dateAndTime.DateAndTimeParameters.StartOrEnd.AllSpinnerParameters;



public class DateAndTimeSetterGuiController extends DateAndTimeParameters
{	
	private class Spinners
	{
		JSpinner year, month, date, time;
	}	
	private Spinners start, end;
	private SpinnerCommonDateModel common_model;
	private Container container;
	
	
	public void addDateAndTimeSetterTo(Container container)
	{
		this.container = container;
		start = addDateAndTimeSetter(START);
		end = addDateAndTimeSetter(END);
	}
	
	
	
	private Spinners addDateAndTimeSetter(StartOrEnd start_or_end)
	{
		Spinners spinners;
		
		addLabel(start_or_end.title);
		spinners = addAllSpinners(start_or_end.spinners);
		addAllLabels(start_or_end.labels);
		return spinners;
	}
	
	
	private void addAllLabels(AllLabelParameters param)
	{
		addLabel(param.year);
		addLabel(param.month);
		addLabel(param.date);
	}
	
	
	
	private void addLabel(LabelParameters param)
	{
		JLabel label;
		label = new JLabel(param.string);
		label.setBounds(param.bounds);
		container.add(label);		
	}



	private Spinners addAllSpinners(AllSpinnerParameters start_or_end)
	{
		Spinners spinners;
		SpinnerCommonDateModel common_model;
		spinners = new Spinners();
		common_model = new SpinnerCommonDateModel();
		
		
		spinners.year = addSpinner(start_or_end.year, common_model);
		spinners.month = addSpinner(start_or_end.month, common_model);
		spinners.date = addSpinner(start_or_end.date, common_model);
		spinners.time = addSpinner(start_or_end.time, common_model);
		
		return spinners;
	}	
	
	
	private JSpinner addSpinner(SpinnerParameters param, SpinnerCommonDateModel common_model)
	{
		int fields[]; String format; Rectangle bounds;
		JSpinner spinner; JSpinner.DateEditor editor;
		JFormattedTextField text_field; DateFormatter formatter;		

		
		fields = param.fields;
		format = param.format;
		bounds = param.bounds;
		
		spinner = new JSpinner(common_model);
		spinner.setBounds(bounds);
		editor = new JSpinner.DateEditor(spinner, format);	
		
		text_field = editor.getTextField();
		text_field.setHorizontalAlignment(JFormattedTextField.CENTER);
		text_field.addFocusListener( new FocusListener() {
				@Override
				public void focusGained(FocusEvent arg0) {
					//System.out.println("focusGained");
					common_model.setFields(fields);
					common_model.setTextField(text_field);
					
				}	
				@Override
				public void focusLost(FocusEvent arg0) {
					//text_field.setValue(common_model.getCalendar().getTime());
					common_model.setFields(fields);
					common_model.setTextField(text_field);
					try {
						text_field.commitEdit();
					} catch (ParseException e) 	{						
						text_field.setValue(common_model.getCalendar().getTime());
					}					
				}
			});	
		formatter = (DateFormatter)text_field.getFormatter();
		formatter.setAllowsInvalid(true); // this makes what you want
		formatter.setOverwriteMode(false);
		formatter.setCommitsOnValidEdit(false);		
		spinner.setEditor(editor);
		container.add(spinner);		
		return spinner;
	}
}
