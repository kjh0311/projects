package kjh.running_machine_exercise_infomation_shower.tab3;

import android.app.DatePickerDialog;
import android.app.Dialog;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.widget.CalendarView;
import android.widget.DatePicker;

import java.util.Calendar;

public class DatePickerFragment extends DialogFragment implements DatePickerDialog.OnDateSetListener
{
	public static final String DATE = "DATE";
	CalendarView calendar_view;
	Dialog dialog;
	// onCreateDialog 가 처음 발생할 때 실행함
	long fisrt_selected_millis;

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState)
    {
		if (dialog == null)
			dialog = create_default_dialog();
		return dialog;
    }


	public Dialog getDialog()
	{
		return dialog;
	}

	public void set_calendar_view(CalendarView calendar_view)
	{
		this.calendar_view = calendar_view;
		// dialog 가 null 이면 null 이 아닐 때까지 대기함
		if (dialog != null)
		{
			calendar_view_to_dialog();
		}
		else
		{
			fisrt_selected_millis = calendar_view.getDate();
		}
	}


	private Dialog create_dialog_by_calendar(Calendar calendar)
	{
		int year, month, day;

		year = calendar.get(Calendar.YEAR);
		month = calendar.get(Calendar.MONTH);
		day = calendar.get(Calendar.DAY_OF_MONTH);

		// Create a new instance of DatePickerDialog and return it
		dialog = new DatePickerDialog(getActivity(), this, year, month, day);
		return dialog;
	}


	public void onDateSet(DatePicker view, int year, int month, int day)
    {
        // Do something with the date chosen by the user
		long long_date;

		long_date = date_to_millis(year, month, day);
		calendar_view.setDate(long_date);
		// view.updateDate(year, month, day);
    }

	private void calendar_view_to_dialog()
	{
		DatePickerDialog dialog;
		DatePicker picker;
		long millis;
		IntDate int_date;

		millis = calendar_view.getDate();
		int_date = millis_to_int_date(millis);

		dialog = (DatePickerDialog) this.dialog;
		picker = dialog.getDatePicker();
		picker.updateDate(int_date.year, int_date.month, int_date.day);
	}


	class IntDate
	{
		int year, month, day;
	}


	private IntDate millis_to_int_date(long millis)
	{
		IntDate int_date;
		Calendar calendar;

		int_date = new IntDate();
		calendar = Calendar.getInstance();
		calendar.setTimeInMillis(millis);

		int_date.year = calendar.get(Calendar.YEAR);
		int_date.month = calendar.get(Calendar.MONTH);
		int_date.day = calendar.get(Calendar.DAY_OF_MONTH);

		return int_date;
	}


	private long date_to_millis(int year, int month, int day)
	{
		Calendar calendar = Calendar.getInstance();
		calendar.set(Calendar.YEAR, year);
		calendar.set(Calendar.MONTH, month);
		calendar.set(Calendar.DAY_OF_MONTH, day);
		return calendar.getTimeInMillis();
	}


	private Dialog create_default_dialog()
	{
		final Calendar calendar;
		calendar = Calendar.getInstance();
		calendar.setTimeInMillis(fisrt_selected_millis);
		return create_dialog_by_calendar(calendar);
	}
}