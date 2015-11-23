//
//  AGSHistoryViewController.swift
//  SampleSwift
//
//  Created by let on 10/29/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit

class AGSHistoryCell: UITableViewCell {
    @IBOutlet weak var dateLabel: UILabel!
    @IBOutlet weak var durationLabel: UILabel!
    
    @IBOutlet weak var callReport: UILabel!
    
    override func awakeFromNib() {
        callReport.text = NSLocalizedString("Conf Report", comment: "")
    }
}


class AGSHistoryViewController: AGSBaseViewController, UITableViewDataSource, UITableViewDelegate {

    var records: [AnyObject] = []
    @IBOutlet weak var tableView: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        records += AGSCoreDataManager.shareManager.allRecords()
        tableView.reloadData()
    }

    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        title = NSLocalizedString("Conf. History", comment: "")
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // MARK: - Table view

    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return records.count
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell: AGSHistoryCell = (tableView.dequeueReusableCellWithIdentifier("HistoryCell", forIndexPath: indexPath) as? AGSHistoryCell)!
        
        let record: Record = (records[indexPath.row] as? Record)!
        
        cell.dateLabel.text = record.date!.dateWithFormat("YYYY-MM-dd")
        cell.durationLabel.text = NSDate.formatStringWithDuration(record.duration!.unsignedLongValue)
        
        return cell
    }
    
    func tableView(tableView: UITableView, heightForRowAtIndexPath indexPath: NSIndexPath) -> CGFloat {
        return 122.0
    }
    
    func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        
        let record: Record = (records[indexPath.row] as? Record)!
        let controller = FOWebViewController(URL: record.url, title: NSLocalizedString("Conf. History", comment: ""))
        navigationController?.pushViewController(controller, animated: true)
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
