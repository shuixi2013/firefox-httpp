/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "nsCOMPtr.h"
#include "udtSocketProvider.h"
#include "udt_pr.h"

//#include "nspr.h"

NS_IMPL_THREADSAFE_ISUPPORTS1(udtSocketProvider, nsISocketProvider)

udtSocketProvider::~udtSocketProvider()
{
}

NS_IMETHODIMP 
udtSocketProvider::NewSocket(PRInt32 aFamily,
                               const char *aHost, 
                               PRInt32 aPort, 
                               const char *aProxyHost, 
                               PRInt32 aProxyPort,
                               PRUint32 aFlags,
                               PRFileDesc * *aFileDesc, 
                               nsISupports **aSecurityInfo)
{
    NS_ENSURE_ARG_POINTER(aFileDesc);
  
    PRFileDesc* udpFD = PR_OpenUDPTransportSocket(aFamily,
            aHost, aPort);
    if (!udpFD)
        return NS_ERROR_FAILURE;
  
    *aFileDesc = udpFD;
    return NS_OK;
}

NS_IMETHODIMP 
udtSocketProvider::AddToSocket(PRInt32 aFamily,
                                 const char *aHost,
                                 PRInt32 aPort,
                                 const char *aProxyHost,
                                 PRInt32 aProxyPort,
                                 PRUint32 aFlags,
                                 struct PRFileDesc * aFileDesc,
                                 nsISupports **aSecurityInfo)
{
    // does not make sense to strap a UDP socket onto an existing socket
    NS_NOTREACHED("Cannot layer UDP socket on an existing socket");
    return NS_ERROR_UNEXPECTED;
}

NS_METHOD
udtSocketProvider::Create(nsISupports *aOuter, REFNSIID aIID, void **aResult)
{
    nsresult rv;
    nsCOMPtr<nsISocketProvider> inst = new udtSocketProvider();
    if (!inst)
        rv = NS_ERROR_OUT_OF_MEMORY;
    else
        rv = inst->QueryInterface(aIID, aResult);
    return rv;
}
