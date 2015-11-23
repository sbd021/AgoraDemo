//
//  Record+CoreDataProperties.swift
//  SampleSwift
//
//  Created by let on 10/29/15.
//  Copyright © 2015 Agora. All rights reserved.
//
//  Choose "Create NSManagedObject Subclass…" from the Core Data editor menu
//  to delete and recreate this implementation file for your updated model.
//

import Foundation
import CoreData

extension Record {

    @NSManaged var callId: String?
    @NSManaged var date: NSDate?
    @NSManaged var duration: NSNumber?
    @NSManaged var url: String?

}
