package com.example.hw2_18

sealed interface SyncStatus {
    data object Idle : SyncStatus
    data object Waiting : SyncStatus
    data object Running : SyncStatus
    data class Done(val message: String?) : SyncStatus
    data class Failed(val message: String) : SyncStatus
}