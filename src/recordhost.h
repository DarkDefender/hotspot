/*
    SPDX-FileCopyrightText: Lieven Hey <lieven.hey@kdab.com>
    SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "jobtracker.h"
#include <QObject>

enum RecordType
{
    LaunchApplication = 0,
    AttachToProcess,
    ProfileSystem,
    NUM_RECORD_TYPES
};
Q_DECLARE_METATYPE(RecordType)

// all of recordpage
//
class RecordHost : public QObject
{
    Q_OBJECT
public:
    explicit RecordHost(QObject* parent = nullptr);
    ~RecordHost() override;

    // might be false when async ops is ongoing internally
    bool isReady() const;
    QString errorMessage() const
    {
        return m_error;
    }

    bool isPerfInstalled() const
    {
        return m_isPerfInstalled;
    }

    QString host() const
    {
        return m_host;
    }
    void setHost(const QString& host);

    // username etc. pp.

    QString currentWorkingDirectory() const
    {
        return m_cwd;
    }
    void setCurrentWorkingDirectory(const QString& cwd);

    QString clientApplication() const
    {
        return m_clientApplication;
    }
    void setClientApplication(const QString& clientApplication);

    QString outputFileName() const
    {
        return m_outputFileName;
    }
    void setOutputFileName(const QString& filePath);

    // perf binary
    // only editable by settings
    QString perfBinary() const;
    // void setPerfBinary(const QString &perfBinary);

    // async query options
    struct PerfCapabilities
    {
        // see all virtuals in PerfRecord can*
        bool canProfileOffCpu = false;
        bool canSampleCpu = false;
        bool canSwitchEvents = false;
        bool canUseAio = false;
        bool canCompress = false;
        bool canElevatePrivileges = false;
        bool privilegesAlreadyElevated = false;
    };
    PerfCapabilities perfCapabilities() const
    {
        // reset member to default all = false when host or perf binary changes
        return m_perfCapabilities;
    }

    RecordType recordType() const
    {
        return m_recordType;
    }
    void setRecordType(RecordType type);

    void setPids(const QStringList& pids);

signals:
    /// disallow "start" on recordpage until this is ready and that should only be the case when there's no error
    void isReadyChanged(bool isReady);
    /// connect to fill UI in recordpage
    void errorOccurred(const QString& message);
    void hostChanged();
    void currentWorkingDirectoryChanged(const QString& cwd); // Maybe QUrl
    void clientApplicationChanged(const QString& clientApplication);
    void perfCapabilitiesChanged(RecordHost::PerfCapabilities perfCapabilities);
    void isPerfInstalledChanged(bool isInstalled);
    void outputFileNameChanged(const QString& outputFileName);
    void recordTypeChanged(RecordType type);
    void pidsChanged();
    // ... more

private:
    bool isLocal() const
    {
        return m_host == QStringLiteral("localhost");
    }

    QString m_host = {};
    QString m_error;
    QString m_cwd;
    QString m_clientApplication;
    QString m_outputFileName;
    bool m_isPerfInstalled = false;
    PerfCapabilities m_perfCapabilities = {};
    JobTracker m_checkPerfCapabilitiesJob;
    JobTracker m_checkPerfInstalledJob;
    RecordType m_recordType = LaunchApplication;
    QStringList m_pids = {};
};

Q_DECLARE_METATYPE(RecordHost::PerfCapabilities);
