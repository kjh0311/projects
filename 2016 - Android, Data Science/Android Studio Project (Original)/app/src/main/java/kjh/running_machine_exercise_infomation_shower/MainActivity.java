package kjh.running_machine_exercise_infomation_shower;


import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;

import kjh.running_machine_exercise_infomation_shower.tab1.Tab1Fragment;
import kjh.running_machine_exercise_infomation_shower.tab2.Tab2Fragment;
import kjh.running_machine_exercise_infomation_shower.tab3.Tab3Fragment;
import kjh.running_machine_exercise_infomation_shower
            .bluetooth_client_fragment.BluetoothClientFragment;


import kjh_custom_tabs.KJH_CustomTabs;

public class MainActivity extends ActionBarActivity
{

	class Fragments
	{
		Tab1Fragment tab1;
		Tab2Fragment tab2;
		Tab3Fragment tab3;
		Fragments()
		{
			tab1 = new Tab1Fragment();
			tab2 = new Tab2Fragment();
			tab3 = new Tab3Fragment();
		}

		public void update()
		{
			tab1.update();
			tab2.update();
			tab3.update();
		}
	}
	/**
	 * The {@link android.support.v4.view.PagerAdapter} that will provide
	 * kjh.running_machine_exercise_infomation_shower.fragments for each of the sections. We use a
	 * {@link FragmentPagerAdapter} derivative, which will keep every
	 * loaded fragment in memory. If this becomes too memory intensive, it
	 * may be best to switch to a
	 * {@link android.support.v4.app.FragmentStatePagerAdapter}.
	 */

	/**
	 * The {@link ViewPager} that will host the section contents.
	 */
	private Fragments fragments;
	private BluetoothClient client;


	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		addAllContents();
	}


	private void addAllContents()
	{
		ViewPager pager;

        setContentView(R.layout.activity_main);
		fragments = new Fragments();
		pager = setViewPagerFragments(fragments);
		setTabsFromViewPager(pager);
		client = new BluetoothClient(this);
		client.connect();
	}


	public void update()
	{
		fragments.update();
	}

	private ViewPager setViewPagerFragments(Fragments fragments)
	{
		FragmentManager fragment_manager;
		SectionsPagerAdapter adapter;
		ViewPager pager;

		fragment_manager = getSupportFragmentManager();
		// Create the adapter that will return a fragment for each of the three
		// primary sections of the activity.
		adapter = new SectionsPagerAdapter
				(fragments, fragment_manager);
		// Set up the ViewPager with the sections adapter.
		pager = (ViewPager) findViewById(R.id.container);
		pager.setAdapter(adapter);
		return pager;
	}

	private void setTabsFromViewPager(ViewPager pager)
	{
		KJH_CustomTabs tabs;

		tabs = (KJH_CustomTabs) findViewById(R.id.tabs);
		tabs.setDistributeEvenly(true);
		tabs.setFromViewPager(pager);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.menu_main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();

		//noinspection SimplifiableIfStatement
		if (id == R.id.action_settings) {
			return true;
		}

		return super.onOptionsItemSelected(item);
	}
}
