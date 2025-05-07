///////////////////////////////////////////////////////////////////////////////
/* \file   slhmivalidator.h
*  \author Carola Fuchs
*  \date   14.9.2009
*  \brief  special Validators for HMI
*
*  This file is part of the HMI Solutionline global classes and utilities
*
*  (C) Copyright Siemens AG I DT MC 2009. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HMI_VALIDATOR_QT_H)
#define SL_HMI_VALIDATOR_QT_H

#include <QtGui/QValidator>

#if !defined(SL_HMI_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT Q_DECL_EXPORT
#       else
#           define SL_HMI_EXPORT Q_DECL_IMPORT
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif

class SlHmiIPAddressValidatorPrivate;

class SL_HMI_EXPORT SlHmiIPAddressValidator : public QValidator
{
  Q_OBJECT
  Q_PROPERTY(bool hostnameAllowed READ hostnameAllowed WRITE setHostnameAllowed)
  Q_PROPERTY(bool isHostname READ isHostname)

public:
  static const QString REG_EXP_IPV4;
  static const QString REG_EXP_HOSTNAME;
  static const QString REG_EXP_HOSTNAME_NO_DOMAIN;

  explicit SlHmiIPAddressValidator(QObject *parent);
  ~SlHmiIPAddressValidator();

  virtual QValidator::State validate(QString& input, int& pos) const;
  virtual QValidator::State validate(const QString& input) const; // validate without changing the string and suggesting a new cursor pos
  virtual void fixup(QString &) const;

  void setHostnameAllowed(bool bHostnameAllowed);
  bool hostnameAllowed(void) const;

  bool isHostname(void) const;

private:
  Q_DISABLE_COPY(SlHmiIPAddressValidator)

  SlHmiIPAddressValidatorPrivate * m_pData;
};

class SlHmiIPAddressValidatorPrivate
{
  public:

  SlHmiIPAddressValidatorPrivate(SlHmiIPAddressValidator* pParent);
  ~SlHmiIPAddressValidatorPrivate();

  SlHmiIPAddressValidator * m_pIPAddressValidator;
  QRegExpValidator * m_pRegExpValidator;
  bool m_bHostnameAllowed;
  bool m_bIsHostname;
};

#endif //!defined(SL_HMI_VALIDATOR_QT_H)
