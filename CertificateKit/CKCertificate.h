//
//  CKCertificate.h
//
//  MIT License
//
//  Copyright (c) 2016 Ian Spence
//  https://github.com/certificate-helper/CertificateKit
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#import <Foundation/Foundation.h>
#import "CKCertificateRevoked.h"

@class CKCertificateRevoked;

@interface CKCertificate : NSObject

/**
 *  Create a CKCertificate object from a pre-existing X509 object.
 *
 *  @param cert A libssl compliant X509 cert.
 *
 *  @return A CKCertificate instance
 */
+ (CKCertificate *) fromX509:(void *)cert;

typedef NSArray<NSURL *> distributionPoints;

typedef NS_ENUM(NSInteger, CKCertificateFingerprintType) {
    // SHA 512 fingerprint type
    CKCertificateFingerprintTypeSHA512,
    // SHA 256 fingerprint type
    CKCertificateFingerprintTypeSHA256,
    // MD5 fingerprint type
    CKCertificateFingerprintTypeMD5,
    // SHA1 fingerprint type
    CKCertificateFingerprintTypeSHA1
};

typedef NS_ENUM(NSInteger, CKCertificateError) {
    // Errors relating to connecting to the remote server.
    CKCertificateErrorConnection,
    // Crypto error usually resulting from being run on an unsupported platform.
    CKCertificateErrorCrypto,
    // Invalid parameter information such as hostnames.
    CKCertificateErrorInvalidParameter
};

@property (strong, nonatomic, readonly) NSString * summary;

/**
 *  If the certificate is an EV certificate. See `extendedValidationAuthority` for more.
 */
@property (nonatomic, readonly) BOOL extendedValidation;

/**
 *  Certificate revocation information
 */
@property (strong, nonatomic) CKCertificateRevoked * revoked;

/**
 *  Returns the SHA256 fingerprint for the certificate
 *
 *  @return A NSString value of the fingerprint
 */
- (NSString *) SHA256Fingerprint;

/**
 *  Returns the MD5 fingerprint for the certificate
 *
 *  Warning! The security of the MD5 algorithm has been seriously compromised - avoid use!
 *
 *  @return A NSString value of the fingerprint
 */
- (NSString *) MD5Fingerprint;

/**
 *  Returns the SHA1 fingerprint for the certificate
 *
 *  Warning! SH1 is no longer considered cryptographically secure - avoid use!
 *
 *  @return A NSString value of the fingerprint
 */
- (NSString *) SHA1Fingerprint;

/**
 *  Verify the fingerprint of the certificate. Useful for certificate pinning.
 *
 *  @param fingerprint The fingerprint
 *  @param type        The type of hashing method used to generate the fingerprint
 *
 *  @return YES if verified
 */
- (BOOL) verifyFingerprint:(NSString *)fingerprint type:(CKCertificateFingerprintType)type;

/**
 *  Returns the serial number for the certificate
 *
 *  @return A NSString value of the serial number
 */
- (NSString *) serialNumber;

/**
 *  Returns the human readable signature algorithm
 *
 *  @return A NSString value of the algorithm
 */
- (NSString *) signatureAlgorithm;

/**
 *  Returns the human readable public key algorithm
 *
 *  @return A NSString value of the algorithm
 */
- (NSString *) keyAlgorithm;

/**
 *  Returns the expiry date for the certificate
 *
 *  @return A NSDate object for the "not after" field - Time is not critical for this date object.
 */
- (NSDate *) notAfter;

/**
 *  Returns the start date for the certificate
 *
 *  @return A NSDate object for the "not before" field - Time is not critical for this date object.
 */
- (NSDate *) notBefore;

/**
 *  Test if current date is within the certificates issue date range
 *
 *  @return current date within range?
 */
- (BOOL) validIssueDate;

/**
 *  Retuns the issuer name
 *
 *  @return A NSString value of the issuer identity
 */
- (NSString *) issuer;

/**
 *  Retruns a dictionary with the subject names, and name types (OU or CN)
 *
 *  @return A dictionary of subject fields
 */
- (NSDictionary<NSString *, NSString *> *) names;

/**
 *  Returns an array of subject names applicable to the cert
 *
 *  @return An array of strings
 */
- (NSArray<NSString *> *) subjectAlternativeNames;

/**
 *  Returns the public key encoded using Privacy-Enhanced Electronic Mail (PEM).
 *
 *  @return NSData representing the bytes (includes header and footer) or nil on error
 */
- (NSData *) publicKeyAsPEM;

/**
 *  Returns the X509 value of the certificate. Safe to cast to (X509 *) if not nil.
 *
 *  @return (X509 *)void pointer representing the X509 struct of the certificate or nil on error
 */
- (void *) X509Certificate;

/**
 *  Returns the authority that manages the extended validation for this certificate.
 *
 *  @return A string representing the authority name, or nil
 */
- (NSString *) extendedValidationAuthority;

/**
 *  Get an array of CRL distributionPoints (an array of URLs)
 *
 *  @return An array of URLs or nil
 */
- (distributionPoints *) crlDistributionPoints;

/**
 *  Get the OpenSSL version used by CKCertificate
 *
 *  @return (NSString *) The OpenSSL version E.G. "1.1.0e"
 */
+ (NSString *) openSSLVersion;
@end