package gui.range_specifying.check_box_for_using_time;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import actions.range_specifying.LookUpActions;
import actions.range_specifying.TimeSpecifyingAllowActions;
import gui.Bounds;
import gui.Strings;
import program_start.Actions;



public class CheckBoxForUsingTimeController
{	
	
	private JCheckBox check_box;	
	public void addCheckBoxTo(Container container)
	{	
		check_box = new JCheckBox(Strings.USING_TIME);
		check_box.setBounds(Bounds.SpecifyRange.USING_TIME);
		check_box.setEnabled(false);
		container.add(check_box);
	}

	public void addActions(TimeSpecifyingAllowActions actions) {
		check_box.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e)
			{
				boolean checked;
				checked = check_box.isSelected();
				actions.set_using_time_for_range_specifying(checked);
			}					
		});
	}

	public void setEnabled(boolean true_or_false)
	{
		check_box.setEnabled(true_or_false);
	}	
}




