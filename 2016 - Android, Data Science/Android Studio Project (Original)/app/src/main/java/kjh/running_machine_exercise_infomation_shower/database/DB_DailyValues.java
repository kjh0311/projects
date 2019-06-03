package kjh.running_machine_exercise_infomation_shower.database;

import android.database.Cursor;

/**
 * Created by com on 2016-02-22.
 */
public class DB_DailyValues
{
	private String date, time, kcal, km;

	private static final int
		TIME = 0, KCAL = 1, KM = 2;

	public DB_DailyValues(Cursor cursor, String date) {
		this.date = date;
		time = cursor.getString(TIME);
		kcal = cursor.getString(KCAL);
		km = cursor.getString(KM);
	}


	public String toString()
	{
		class Converted {
			String date, time, kcal, km;
		}
		DB_ValueConverter converter;
		Converted converted;
		StringBuilder daily_values;

		converter = new DB_ValueConverter();
		converted = new Converted();
		daily_values = new StringBuilder();

		converted.date = converter.convert_date(date);
		converted.time = converter.convert_total_time(time);
		converted.kcal = converter.convert_total_kcal(kcal);
		converted.km = converter.convert_total_km(km);

		daily_values.append(converted.date);
		daily_values.append("\n\n");
		daily_values.append(converted.time);
		daily_values.append("\n");
		daily_values.append(converted.kcal);
		daily_values.append("\n");
		daily_values.append(converted.km);
		daily_values.append("\n");


		return daily_values.toString();
	}
}
