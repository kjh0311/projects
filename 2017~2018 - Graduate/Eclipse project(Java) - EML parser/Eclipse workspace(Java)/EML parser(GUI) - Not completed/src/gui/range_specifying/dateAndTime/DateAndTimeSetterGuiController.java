package gui.range_specifying.dateAndTime;
import java.awt.AWTException;
import java.awt.Component;
import java.awt.Container;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.Robot;
import java.awt.event.ActionEvent;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.InputEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.text.ParseException;
import java.util.Calendar;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JButton;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JSpinner;
import javax.swing.SwingUtilities;
import javax.swing.event.AncestorEvent;
import javax.swing.event.AncestorListener;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.text.DateFormatter;

import gui.range_specifying.dateAndTime.DateAndTimeParameters.StartOrEnd.AllLabelParameters;
import gui.range_specifying.dateAndTime.DateAndTimeParameters.StartOrEnd.AllSpinnerParameters;




public class DateAndTimeSetterGuiController extends DateAndTimeParameters
{	
	class Spinners
	{
		SpinnerCommonDateModel common_model;
		JSpinner year, month, date, time;
		public void setDateEnabled(boolean true_or_false)
		{
			year.setEnabled(true_or_false);
			month.setEnabled(true_or_false);
			date.setEnabled(true_or_false);
		}
	}
	
	
	class Labels {
		JLabel title, year, month, date;
		public void setEnabled(boolean true_or_false)
		{
			title.setEnabled(true_or_false);
			year.setEnabled(true_or_false);
			month.setEnabled(true_or_false);
			date.setEnabled(true_or_false);
		}
	}
	
	
	class DateAndTimeSetter {
		Spinners spinners;
		Labels labels;
		public void setDateEnabled(boolean true_or_false)
		{
			spinners.setDateEnabled(true_or_false);
			labels.setEnabled(true_or_false);
		}
		public void setTimeEnabled(boolean true_or_false)
		{
			spinners.time.setEnabled(true_or_false);			
		}
	}
	
	private DateAndTimeSetter start, end;
	private Container container;
	private boolean date_enabled;
	private boolean time_enabled;
	
	
	public DateAndTimeSetterGuiController()
	{
		date_enabled = false;
		time_enabled = false;
	}	
	
	public void addDateAndTimeSetterTo(Container container)
	{
		this.container = container;
		start = addDateAndTimeSetter(DateAndTimeParameters.START);
		end = addDateAndTimeSetter(DateAndTimeParameters.END);
		end.spinners.common_model.setLowerLimitModel
		(start.spinners.common_model);
	}
	
	
	
	private DateAndTimeSetter addDateAndTimeSetter(StartOrEnd start_or_end)
	{
		DateAndTimeSetter date_and_time_setter;
		
		date_and_time_setter = new DateAndTimeSetter();
		
		date_and_time_setter.labels = addAllLabels(start_or_end.labels);
		date_and_time_setter.spinners = addAllSpinners(start_or_end.spinners);		
		return date_and_time_setter;
	}
	
	
	private Labels addAllLabels(AllLabelParameters param)
	{
		Labels labels;		
		labels = new Labels();
		labels.title = addLabel(param.title);
		labels.year = addLabel(param.year);
		labels.month = addLabel(param.month);
		labels.date = addLabel(param.date);
		
		Font font = labels.title.getFont();
		font = font.deriveFont(Font.BOLD);
		labels.title.setFont(font);
		return labels;
	}
	
	
	
	private JLabel addLabel(LabelParameters param)
	{
		JLabel label;
		label = new JLabel(param.string);
		label.setBounds(param.bounds);
		label.setEnabled(false);
		container.add(label);
		return label;
	}



	private Spinners addAllSpinners(AllSpinnerParameters start_or_end)
	{
		Spinners spinners;
		SpinnerCommonDateModel common_model;
		
		spinners = new Spinners();
		common_model = new SpinnerCommonDateModel();
		spinners.common_model = common_model;
		start_or_end.common.model = common_model;		
		
		spinners.year = addSpinner(start_or_end.year);
		spinners.month = addSpinner(start_or_end.month);
		spinners.date = addSpinner(start_or_end.date);
		spinners.time = addSpinner(start_or_end.time);
		
		//spinners.setEnabled(false);
		
		return spinners;
	}	
	
	
	private JSpinner addSpinner(SpinnerParameters param)//, SpinnerCommonDateModel common_model)
	{
		JSpinner spinner;
		Rectangle bounds;
		SpinnerCommonDateModel common_model;
		String format; int selected_fields[];
		JSpinner.DateEditor editor;
		JFormattedTextField text_field; DateFormatter formatter;
		
		
		bounds = param.bounds;
		format = param.FORMAT;
		selected_fields = param.FIELDS;
		common_model = param.COMMON.model;
		
		
		spinner = new JSpinner();		
		spinner.setBounds(bounds);
		spinner.setEnabled(false);
		spinner.setModel(common_model);		
		editor = new JSpinner.DateEditor(spinner, format);
		spinner.setEditor(editor);		
		
		
		text_field = editor.getTextField();		
		text_field.setHorizontalAlignment(JFormattedTextField.CENTER);
		text_field.addFocusListener( new FocusListener() {
				@Override
				public void focusGained(FocusEvent arg0) {			
					common_model.setEditedFields(selected_fields);
					common_model.setTextField(text_field);									
				}	
				
				@Override
				public void focusLost(FocusEvent arg0) {
					common_model.setEditedFields(selected_fields);
					common_model.setTextField(text_field);
					try {
						text_field.commitEdit();						
					} catch (ParseException e) {						
						text_field.setValue(common_model.getCalendar().getTime());
					}
				}
			});
		
		
		text_field.addMouseListener(new MouseListener() {

			@Override
			public void mouseClicked(MouseEvent arg0)
			{
				
				if (text_field.getSelectedText()==null) {				
					try
					{
						Robot r = new Robot();
						
						r.mousePress(InputEvent.BUTTON1_MASK);
						r.mouseRelease(InputEvent.BUTTON1_MASK);
						
					} catch (AWTException e)
					{
						e.printStackTrace();
					}
				}
			}

			@Override
			public void mouseEntered(MouseEvent arg0)
			{
				// TODO Auto-generated method stub
				
			}

			@Override
			public void mouseExited(MouseEvent arg0)
			{
				// TODO Auto-generated method stub
				
			}

			@Override
			public void mousePressed(MouseEvent arg0)
			{
				// TODO Auto-generated method stub
				
			}

			@Override
			public void mouseReleased(MouseEvent arg0)
			{
				// TODO Auto-generated method stub
				
			}			
		});		
		//notify_to_common_model_when_arrow_button_clicked(common_model, spinner);		
		formatter = (DateFormatter)text_field.getFormatter();
		formatter.setAllowsInvalid(true); // this makes what you want
		formatter.setOverwriteMode(true);
		formatter.setCommitsOnValidEdit(false);
		
		container.add(spinner);		
		return spinner;
	}


	public void setStartAndEndCalendar(Calendar start_calendar, Calendar end_calendar)
	{		
		start.spinners.common_model.setCalendar(start_calendar);
		end.spinners.common_model.setCalendar(end_calendar);
	}


	public void setDateEnabled(boolean true_or_false)
	{
		date_enabled = true_or_false;
		start.setDateEnabled(true_or_false);
		end.setDateEnabled(true_or_false);
		if (date_enabled == true && time_enabled == true) {
			start.setTimeEnabled(true);
			end.setTimeEnabled(true);
		} else if (date_enabled == false) {
			start.setTimeEnabled(false);
			end.setTimeEnabled(false);
		}
	}
	
	
	public void setTimeEnabled(boolean true_or_false)
	{
		if (date_enabled) {
			start.setTimeEnabled(true_or_false);
			end.setTimeEnabled(true_or_false);
		}
		time_enabled = true_or_false;
	}
}
