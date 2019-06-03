package kjh.running_machine_exercise_infomation_shower;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

import kjh.running_machine_exercise_infomation_shower.tab1.Tab1Fragment;
import kjh.running_machine_exercise_infomation_shower.tab2.Tab2Fragment;

/**
 * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
 * one of the sections/tabs/pages.
 */
public class SectionsPagerAdapter extends FragmentPagerAdapter
{
	MainActivity.Fragments fragments;
	public SectionsPagerAdapter(MainActivity.Fragments fragments, FragmentManager fm)
	{
		super(fm);
		this.fragments = fragments;
	}

	private final String TITLES[] =
			new String[]{"사용자 입력", "운동기록", "달력"};
	private final int
			USER_INPUT = 0, EXERCISE_RECORD = 1, CALENDER = 2;

	@Override
	public Fragment getItem(int position)
	{
		switch (position)
		{
			// 자기자신을 객체화 시켜서 보낼 때는 this 를 사용
			case USER_INPUT:
				return fragments.tab1;
			case EXERCISE_RECORD:
				return fragments.tab2;
			case CALENDER:
			default:
				return fragments.tab3;
		}
		// getItem is called to instantiate the fragment for the given page.
		// Return a PlaceholderFragment (defined as a static inner class below).
		// return PlaceholderFragment.newInstance(position + 1);
	}

	@Override
	public int getCount()
	{
		return TITLES.length;
	}

	@Override
	public CharSequence getPageTitle(int position)
	{
		return TITLES[position];
	}
}