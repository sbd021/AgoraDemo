//
//  AGSFrostedViewController.swift
//  SampleSwift
//
//  Created by let on 10/29/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit

class AGSFrostedViewController: REFrostedViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func awakeFromNib() {
        let loginStoryboard = UIStoryboard(name: "Login", bundle: nil)
        let menuStoryboard = UIStoryboard(name: "Menu", bundle: nil)
        let navigationController = loginStoryboard.instantiateViewControllerWithIdentifier("Navigation") as? UINavigationController
        
        contentViewController = navigationController
        menuViewController = menuStoryboard.instantiateViewControllerWithIdentifier("Menu")
        limitMenuViewSize = true
        direction = REFrostedViewControllerDirection.Right
        menuViewSize = CGSizeMake(208, menuViewSize.height)
        panGestureEnabled = false
        
        let delegate = UIApplication.sharedApplication().delegate as? AppDelegate
        navigationController?.delegate = delegate
        delegate?.navigationController = navigationController
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
