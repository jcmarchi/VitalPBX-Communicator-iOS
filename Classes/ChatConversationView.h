/* ChatRoomViewController.h
 *
 * Copyright (C) 2012  Belledonne Comunications, Grenoble, France
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#import <UIKit/UIKit.h>
#import <QuickLook/QLPreviewItem.h>
#import <QuickLook/QLPreviewController.h>

#import "UIToggleButton.h"
#import "UICompositeView.h"
#import "ChatConversationTableView.h"
#import "ImagePickerView.h"
#import "OrderedDictionary.h"
#import "UIRoundedImageView.h"
#import "UIBackToCallButton.h"
#import "Utils/HPGrowingTextView/HPGrowingTextView.h"
#import "UIImageViewDeletable.h"
#import "UIConfirmationDialog.h"

#include "linphone/linphonecore.h"

//Quicklook Preview Item
@interface PreviewItem : NSObject <QLPreviewItem>
@property(readonly, nonatomic) NSURL    *previewItemURL;
@property(readonly, nonatomic) NSString *previewItemTitle;
@end

//QuickLook Datasource for rending PDF docs
@interface FileDataSource : NSObject <QLPreviewControllerDataSource>
@property (strong, nonatomic) PreviewItem *item;
@end

@interface ChatConversationView
	: TPMultiLayoutViewController <HPGrowingTextViewDelegate, UICompositeViewDelegate, ImagePickerDelegate, ChatConversationDelegate,
                        UIDocumentInteractionControllerDelegate, UISearchBarDelegate, UIImageViewDeletableDelegate,QLPreviewControllerDelegate, UICollectionViewDataSource,UIDocumentMenuDelegate,UIDocumentPickerDelegate> {
	OrderedDictionary *imageQualities;
	BOOL scrollOnGrowingEnabled;
	BOOL composingVisible;
    UIConfirmationDialog *securityDialog;
    UIRefreshControl *refreshControl;
}

@property(nonatomic) LinphoneChatRoom *chatRoom;
@property(nonatomic) LinphoneChatRoomCbs *chatRoomCbs;
@property(nonatomic) Boolean markAsRead;

@property (strong, nonatomic) FileDataSource *FileDataSource;

@property(weak, nonatomic) IBOutlet UIIconButton *backButton;
@property(nonatomic, strong) IBOutlet ChatConversationTableView *tableController;
@property(weak, nonatomic) IBOutlet HPGrowingTextView *messageField;
@property(weak, nonatomic) IBOutlet UIView *topBar;
@property(nonatomic, strong) IBOutlet UIButton *sendButton;
@property(nonatomic, strong) IBOutlet UILabel *addressLabel;
@property(nonatomic, strong) IBOutlet UIView *chatView;
@property(nonatomic, strong) IBOutlet UIView *messageView;
@property(nonatomic, strong) IBOutlet UITapGestureRecognizer *listTapGestureRecognizer;
@property(nonatomic, strong) IBOutlet UISwipeGestureRecognizer *listSwipeGestureRecognizer;
@property(strong, nonatomic) IBOutlet UILabel *composeLabel;
@property(strong, nonatomic) IBOutlet UIView *composeIndicatorView;
@property(nonatomic, strong) IBOutlet UIButton *pictureButton;
@property(weak, nonatomic) IBOutlet UIIconButton *callButton;
@property(weak, nonatomic) IBOutlet UIBackToCallButton *backToCallButton;
@property (weak, nonatomic) IBOutlet UIIconButton *infoButton;
@property (weak, nonatomic) IBOutlet UILabel *particpantsLabel;
//@property (nonatomic, strong) UIDocumentInteractionController *documentInteractionController;
@property NSMutableArray <UIImage *> *imagesArray;
@property NSMutableArray <NSString *> *assetIdsArray;
@property NSMutableArray <NSNumber *> *qualitySettingsArray;
@property (weak, nonatomic) IBOutlet UICollectionView *imagesCollectionView;
@property (weak, nonatomic) IBOutlet UIView *imagesView;
@property (weak, nonatomic) IBOutlet UIButton *encryptedButton;

+ (void)markAsRead:(LinphoneChatRoom *)chatRoom;

- (void)configureForRoom:(BOOL)editing;
- (IBAction)onBackClick:(id)event;
- (IBAction)onEditClick:(id)event;
- (IBAction)onMessageChange:(id)sender;
- (IBAction)onSendClick:(id)event;
- (IBAction)onPictureClick:(id)event;
- (IBAction)onListTap:(id)sender;
- (IBAction)onCallClick:(id)sender;
- (IBAction)onDeleteClick:(id)sender;
- (IBAction)onEditionChangeClick:(id)sender;
- (IBAction)onEncryptedDevicesClick:(id)sender;
- (void)update;
- (void)openFileWithURL:(NSURL *)url;
- (void)clearMessageView;

- (void)showFileDownloadError;
- (void)autoDownload:(LinphoneChatMessage *)message view:(ChatConversationView *)view;
- (NSURL *)getICloudFileUrl:(NSString *)name;
- (BOOL)writeFileInICloud:(NSData *)data fileURL:(NSURL *)fileURL;

@end
