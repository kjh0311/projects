package gui.range_specifying.radioButton;
import java.awt.Container;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JRadioButton;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import actions.range_specifying.LookUpActions;
import actions.range_specifying.RadioButtonActions;
import gui.Bounds;
import gui.Strings;


public class RadioButtonGuiController
{
	
	private JRadioButton all, range;	
	
	public void addRadioButtonsTo(Container container)
	{
		ButtonGroup group;
		group = new ButtonGroup();	
		all = addRadioButton(RadioButtonParameters.ALL, group, container);
		range = addRadioButton(RadioButtonParameters.RANGE, group, container);
	}
	
	
	private JRadioButton addRadioButton(RadioButtonParameters.Data data, ButtonGroup group, Container container) {
		JRadioButton rb;		
		rb = new JRadioButton(data.string);
		rb.setSelected(data.checked);
		rb.setBounds(data.bounds);
		rb.setEnabled(false);
		group.add(rb);
		container.add(rb);
		return rb;
	}


	public void setEnabled(boolean true_or_false)
	{
		all.setEnabled(true_or_false);
		range.setEnabled(true_or_false);
	}
	
	
	public void addActions(RadioButtonActions actions) {
		
		ChangeListener l;
		l = new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent event)
			{
				boolean range_specifying_mode;
				
				range_specifying_mode = range.isSelected();
				
				actions.setRangeSpecifyingMode(range_specifying_mode);
				//System.out.println("라디오 버튼 상태 변경");
			}
		};
		
		
		all.addChangeListener(l);
		range.addChangeListener(l);
	}	
}




