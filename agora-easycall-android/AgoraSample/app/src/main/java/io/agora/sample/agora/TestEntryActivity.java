package io.agora.sample.agora;

import io.agora.sample.agora.Model.TestCase;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

public class TestEntryActivity extends BaseActivity {

    private ListView mTestCaseList;
    private List<TestCase> mTestCases = new ArrayList<TestCase>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.requestWindowFeature(Window.FEATURE_NO_TITLE);
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_test_entry);

        initTestCaseList();
        initViews();
        setupListView();
    }


    @Override
    public void onUserInteraction(View view) {
        switch (view.getId()) {
            default:
                super.onUserInteraction(view);
                break;
        }
    }


    private void initTestCaseList() {
        mTestCases.add(new TestCase("join-leave test", "api-test1"));
        mTestCases.add(new TestCase("networkTest","api-test2"));
    }

    private void initViews() {
        mTestCaseList = (ListView) findViewById(R.id.testcase_listview);
    }


    private void setupListView() {
        TestcaseAdapter adapter = new TestcaseAdapter(this, mTestCases);
        mTestCaseList.setAdapter(adapter);
    }

    private class TestcaseAdapter extends BaseAdapter {
        private Context context;
        private List<TestCase> items = new ArrayList<TestCase>();

        public TestcaseAdapter(Context context, List<TestCase> items) {
            super();
            this.context = context;
            this.items.addAll(items);
        }

        @Override
        public int getCount() {
            return this.items.size();
        }

        @Override
        public Object getItem(int position) {
            return this.items.get(position);
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {

            ViewHolder holder;
            if (convertView == null) {
                holder = new ViewHolder();
                convertView = LayoutInflater.from(context).inflate(R.layout.testcase_item_layout, null);
                convertView.setTag(holder);

                holder.itemLayout = (RelativeLayout) convertView.findViewById(R.id.testcast_item);
                holder.itemName = (TextView) convertView.findViewById(R.id.test_name);
                holder.itemResult = (TextView) convertView.findViewById(R.id.test_result);
            } else {
                holder = (ViewHolder) convertView.getTag();
            }

            holder.itemName.setText(mTestCases.get(position).getName());
            holder.itemResult.setText(mTestCases.get(position).getResult().toString());

            final int number = position;
            holder.itemLayout.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    Intent i = new Intent(TestEntryActivity.this, BaseTestActivity.class);
                    startActivity(i);
                }
            });
            return convertView;
        }
    }

    private class ViewHolder {
        private RelativeLayout itemLayout;
        private TextView itemName;
        private TextView itemResult;
    }


}
